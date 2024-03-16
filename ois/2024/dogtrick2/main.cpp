#include <bits/stdc++.h>
#define MAXN 250005

using namespace std;

typedef long long ll;

int n_nodes;
int sequence[MAXN];
vector<int> graph[MAXN];

int scc_curr_time = 0;
int scc_visit_time[MAXN];
int scc_low_link[MAXN];
bool scc_on_stack[MAXN];
stack<int> scc_stack;

int ccs_count;
int ccs[MAXN];

unordered_set<ll> edges;

int ccs_visit_index;
int ccs_last_visit[MAXN];
vector<int> ccs_vertices[MAXN];

ll hash_edge(int a, int b) { return (ll)a * MAXN + b; }

void strong_connect_dfs(int node) {
    scc_visit_time[node] = ++scc_curr_time;
    scc_low_link[node] = scc_visit_time[node];
    scc_stack.push(node);
    scc_on_stack[node] = true;

    for (auto j : graph[node]) {
        if (scc_visit_time[j] == 0) {
            strong_connect_dfs(j);
            scc_low_link[node] = min(scc_low_link[node], scc_low_link[j]);
        } else if (scc_on_stack[j]) {
            scc_low_link[node] = min(scc_low_link[node], scc_visit_time[j]);
        }
    }

    if (scc_low_link[node] == scc_visit_time[node]) {
        int j = -1;
        while (j != node) {
            j = scc_stack.top();
            scc_on_stack[j] = false;
            scc_stack.pop();
            ccs[j] = ccs_count;
            ccs_vertices[ccs_count].push_back(j);
        }
        ccs_count += 1;
    }
}

void strong_connect() {
    for (int i = 0; i < n_nodes; i++) {
        if (scc_visit_time[i] == 0) {
            strong_connect_dfs(i);
        }
    }
}

bool ccs_dag_reachable(int node, int target) {
    ccs_last_visit[node] = ++ccs_visit_index;

    for (; node > target; node--) {
        if (ccs_last_visit[node] != ccs_visit_index) {
            continue;
        }

        for (auto i : ccs_vertices[node]) {
            for (auto j : graph[i]) {
                ccs_last_visit[ccs[j]] = ccs_visit_index;
            }
        }
    }

    return ccs_last_visit[target] == ccs_visit_index;
}

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int seq_length = fastin();
    n_nodes = fastin();
    for (int i = 0; i < seq_length; i++) {
        sequence[i] = fastin();
        sequence[i]--;
    }

    int m_branches = fastin();
    for (int i = 0; i < m_branches; i++) {
        int a = fastin(), b = fastin();
        a--, b--;
        graph[a].push_back(b);
        edges.insert(hash_edge(a, b));
    }

    strong_connect();

    int score = 2;
    for (int i = 1; i < seq_length; i++) {
        int old_trick = sequence[i - 1];
        int new_trick = sequence[i];

        // check if there's an edge
        if (edges.find(hash_edge(old_trick, new_trick)) != edges.end()) {
            score += 2;
        } else if (ccs_dag_reachable(ccs[old_trick], ccs[new_trick])) {
            score += 1;
        } else {
            break;
        }
    }

    cout << score << "\n";
}
