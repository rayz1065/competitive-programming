#include <cassert>
#include <tuple>
#include <utility>
#include <vector>
#include <map>
#include <iostream>

struct VisitSet {
  std::vector<int> v;
  int v_id = 1;

  VisitSet() = default;
  VisitSet(int N) : v(N) {}

  void resize(int N) { v.assign(N, v_id); }

  void reset() { v_id++; }

  void visit(int x) { v[x] = v_id; }

  bool visited(int x) const { return v[x] == v_id; }
};

template <class T>
struct DoubleBuffer {
  std::vector<T> buf[2];

  void push(const T& x) { buf[1].push_back(x); }
  T& back() {
    if (buf[0].size() == 0) swap(buf[0], buf[1]);
    return buf[0].back();
  }
  void pop() { buf[0].pop_back(); }
  bool empty() const { return buf[0].size() == 0 && buf[1].size() == 0; }
  void clear() {
    buf[0].clear();
    buf[1].clear();
  }
};

struct Dinic {
  using pii = std::pair<int, int>;
  std::vector<std::tuple<int, int, int, int>> edges;
  std::vector<std::vector<int>> adj;
  VisitSet vis;
  std::vector<int> level;
  std::vector<int> next_edge;
  DoubleBuffer<int> buf;

  Dinic(int N) : adj(N), vis(N), level(N), next_edge(N) {}
  Dinic() = default;

  void resize(int N) {
    adj.assign(N, {});
    vis.resize(N);
    level.resize(N);
    next_edge.resize(N);
  }
  void clear() {
    edges.clear();
    buf.clear();
    adj.clear();
  }
  void add_edge(int from, int to, int capacity) {
    edges.push_back({from, to, capacity, 0});
    edges.push_back({to, from, 0, 0});
    adj[from].push_back(edges.size() - 2);
    adj[to].push_back(edges.size() - 1);
  }
  bool bfs(int src, int sink) {
    vis.reset();
    buf.clear();
    vis.visit(src);
    level[src] = 0;
    buf.push(src);
    while (!buf.empty()) {
      auto curr = buf.back();
      buf.pop();
      for (int edge_id : adj[curr]) {
        auto [from, to, cap, flow] = edges[edge_id];
        if (cap - flow > 0 && !vis.visited(to)) {
          vis.visit(to);
          level[to] = level[curr] + 1;
          buf.push(to);
        }
      }
    }
    return vis.visited(sink);
  }

  void augment(int edge_id, int bottleneck) {
    auto& [from1, to1, cap1, flow1] = edges[edge_id];
    auto& [from2, to2, cap2, flow2] = edges[edge_id ^ 1];
    flow1 += bottleneck;
    flow2 -= bottleneck;
  }
  int dfs(int curr, int sink, int bottleneck) {
    if (curr == sink) return bottleneck;
    const int num_edges = adj[curr].size();
    for (; next_edge[curr] < num_edges; ++next_edge[curr]) {
      int edge_id = adj[curr][next_edge[curr]];
      auto [from, to, cap, flow] = edges[edge_id];
      if (cap - flow > 0 && level[to] == level[from] + 1) {
        int pushed_flow = dfs(to, sink, std::min(bottleneck, cap - flow));
        if (pushed_flow > 0) {
          augment(edge_id, pushed_flow);
          return pushed_flow;
        }
      }
    }
    return 0;
  }

  std::pair<int, std::vector<std::tuple<int, int, int>>> solve(int src, int sink) {
    int max_flow = 0;
    while (bfs(src, sink)) {
      fill(begin(next_edge), end(next_edge), 0);
      for (int flow = dfs(src, sink, 1u << 30); flow != 0; flow = dfs(src, sink, 1u << 30)) max_flow += flow;
    }
    std::vector<std::tuple<int, int, int>> flow_edges;
    for (int i = 0; i < (int)edges.size(); i += 1) {
      auto [from, to, cap, flow] = edges[i];
      if (flow > 0) {
        assert(cap > 0);
        flow_edges.push_back({from, to, flow});
      }
    }
    return std::pair{max_flow, flow_edges};
  }
};

#define MAXN 10500
#define MAX_PROBLEMS 2505
using namespace std;

typedef long long int lli;

int n;
const int SORGENTE = 0;
const int COPPIE_NUMERI = 1;
const int RISULTATI = COPPIE_NUMERI + MAX_PROBLEMS + 100;
const int POZZO = RISULTATI + 3 * MAX_PROBLEMS + 100;

pair<lli, lli> numbers[MAX_PROBLEMS];

vector<int> grafo[MAXN];

map<lli, int> resultNode;

int n_diff_results = 0;
vector<lli> possibleResults;

int getResultNode(lli result) {
  if (resultNode.find(result) != resultNode.end()) return resultNode[result];
  possibleResults.push_back(result);
  return resultNode[result] = n_diff_results++;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> numbers[i].first >> numbers[i].second;
  }

  auto solver = Dinic(MAXN);

  for (int i = 0; i < n; i++) {
    grafo[SORGENTE].push_back(i + COPPIE_NUMERI);
    grafo[i + COPPIE_NUMERI].push_back(SORGENTE);

    solver.add_edge(SORGENTE, i+COPPIE_NUMERI, 1);

    int a = getResultNode(numbers[i].first + numbers[i].second);
    int b = getResultNode(numbers[i].first - numbers[i].second);
    int c = getResultNode(numbers[i].first * numbers[i].second);

    grafo[i + COPPIE_NUMERI].push_back(a + RISULTATI);
    grafo[i + COPPIE_NUMERI].push_back(b + RISULTATI);
    grafo[i + COPPIE_NUMERI].push_back(c + RISULTATI);

    solver.add_edge(i+COPPIE_NUMERI, a+RISULTATI, 1);
    solver.add_edge(i+COPPIE_NUMERI, b+RISULTATI, 1);
    solver.add_edge(i+COPPIE_NUMERI, c+RISULTATI, 1);

    grafo[a + RISULTATI].push_back(i + COPPIE_NUMERI);
    grafo[b + RISULTATI].push_back(i + COPPIE_NUMERI);
    grafo[c + RISULTATI].push_back(i + COPPIE_NUMERI);
  }

  for (auto j : possibleResults) {
    grafo[resultNode[j] + RISULTATI].push_back(POZZO);
    grafo[POZZO].push_back(resultNode[j] + RISULTATI);

    solver.add_edge(resultNode[j] + RISULTATI, POZZO, 1);
  }

  auto [value, edges] = solver.solve(SORGENTE, POZZO);

  if(value != n) {
    std::cout << "impossible\n";
    return 0;
  }

  auto assigned_result = std::vector<long long>(n);
  for(auto [from, to, flow] : edges) {
    if(from != SORGENTE && to != POZZO) {
      int pair_idx = from - COPPIE_NUMERI;
      int res_idx = to - RISULTATI;
      assigned_result[pair_idx] = possibleResults[res_idx];
    }
  }

  for(int i=0; i < (int)assigned_result.size(); ++i) {
    auto result = assigned_result[i];
    auto [a,b] = numbers[i];
    if(a+b == result) std::cout << a << " + " << b << " = " << a+b << '\n';
    else if(a-b == result) std::cout << a << " - " << b << " = " << a-b << "\n";
    else std::cout << a << " * " << b << " = " << a*b << '\n';
  }
}
