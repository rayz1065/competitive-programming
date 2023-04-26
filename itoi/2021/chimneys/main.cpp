#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define MAXM 10005
#define MAXN 100005

using namespace std;

typedef long long ll;
chrono::_V2::system_clock::time_point start_time;


void set_timer () {
    start_time = chrono::high_resolution_clock::now();
}

bool is_timeout (int max_time) {
    auto elapsed = chrono::high_resolution_clock::now() - start_time;
    ll milliseconds = chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    return milliseconds > max_time;
}
bool is_timeout () {
    return is_timeout(9750);
}

struct Branch {
    int id;
    int a_from;
    int b_to;
    ll length;
} branches[MAXM];
int m_branches;

struct Path {
    int first;
    ll length;

    bool operator < (const Path &other) const {
        return this->length == other.length
            ? this->first < other.first
            : this->length < other.length;
    }
};

vector<int> graph[MAXN];
vector<int> backward_graph[MAXN];

int path_next[MAXN];
int path_prev[MAXN];
set<Path> paths;

int path_start (int edge) {
    return path_prev[edge] == -1 ? edge : path_start(path_prev[edge]);
}
int path_end (int edge) {
    return path_next[edge] == -1 ? edge : path_start(path_next[edge]);
}
ll path_length_from (int edge) {
    ll s = 0;
    for (; edge != -1; edge = path_next[edge]) {
        s += branches[edge].length;
    }
    return s;
}
int path_branches_count_from (int edge) {
    int s = 0;
    for (; edge != -1; edge = path_next[edge]) {
        s += 1;
    }
    return s;
}
Path get_path (int edge) {
    edge = path_start(edge);
    ll length = path_length_from(edge);
    return { edge, length };
}

void concat_edges (int a, int b) {
    assert(branches[a].b_to == branches[b].a_from);
    assert(path_next[a] == -1 && path_prev[b] == -1);
    path_next[a] = b;
    path_prev[b] = a;
}
void remove_next (int a) {
    int b = path_next[a];
    path_prev[b] = -1;
    path_next[a] = -1;
}
void remove_prev (int b) {
    remove_next(path_prev[b]);
}

int shortest_path_from (int node) {
    // find the shortest path starting from this node
    int shortest = -1;
    ll shortest_length = LONG_LONG_MAX >> 1;
    for (auto j: graph[node]) {
        ll length;
        if (path_prev[j] == -1 && (length = path_length_from(j)) < shortest_length) {
            shortest_length = length;
            shortest = j;
        }
    }
    return shortest;
}
void recompute_paths () {
    // clears the paths and recomputes them
    paths.clear();
    for (int i = 0; i < m_branches; i++) {
        if (path_prev[i] == -1) {
            paths.insert({ i, path_length_from(i) });
        }
    }
}
void greedy_solution () {
    // optimal solution for trees
    for (int i = MAXN - 1; i >= 0; i--) {
        for (auto j: graph[i]) {
            assert(path_prev[j] == -1);
            int shortest = shortest_path_from(branches[j].b_to);
            if (shortest == -1) {
                continue ;
            }
            concat_edges(j, shortest);
        }
    }
    recompute_paths();
}


void print_sol () {
    cerr << "worst score: " << paths.begin()->length << "\n";
    cout << paths.size() << "\n";
    for (auto path: paths) {
        cout << path_branches_count_from(path.first) << "\n";
        for (int branch = path.first; branch != -1; branch = path_next[branch]) {
            cout << branches[branch].id << " ";
        }
        cout << "\n";
    }
}

pair<int, ll> has_start_intersection (Path path) {
    // finds an intersection at the start of this path which extends it
    // and keeps the overall score higher than the current one
    int best = -1;
    ll best_len = 0;
    ll smallest_length = paths.begin()->length;
    for (auto j: backward_graph[branches[path.first].a_from]) {
        int next_edge = path_next[j];
        assert(next_edge != -1);
        ll remaining_length = path_length_from(next_edge);
        if (remaining_length <= smallest_length) {
            continue ;
        }
        int j_start = path_start(j);
        ll new_len = path_length_from(j_start) - remaining_length;
        if (new_len > best_len) {
            best_len = new_len;
            best = j;
            // if (backward_graph[branches[path.first].a_from].size() > 500) {
            //     return { best, best_len};
            // }
        }
    }
    return { best, best_len };
}

typedef vector<int> CombinedBranches;
ll combined_branches_length (CombinedBranches x) {
    ll s = 0;
    for (auto i: x) {
        s += branches[i].length;
    }
    return s;
}

vector<int> path_branches (int edge) {
    vector<int> s;
    for (; edge != -1; edge = path_next[edge]) {
        s.push_back(edge);
    }
    return s;
}

vector<int> vector_combine (vector<int> &a, vector<int> &b) {
    vector<int> s;
    for (auto i: a) s.push_back(i);
    for (auto i: b) s.push_back(i);
    return s;
}

bool sort_by_start (int branch_a, int branch_b) {
    return branches[branch_a].a_from < branches[branch_b].a_from;
}

bool find_repartition_2 (Path p1, Path p2) {
    vector<int> edge_path = path_branches(p1.first), j_path = path_branches(p2.first);
    vector<int> free_branches = vector_combine(edge_path, j_path);
    sort(free_branches.begin(), free_branches.end(), sort_by_start);

    // combine the branches to keep only the intersections
    vector<pair<CombinedBranches, CombinedBranches>> all_combinations;
    pair<CombinedBranches, CombinedBranches> curr;

    // find the start
    int start_equal = 0;
    while (
        start_equal + 1 < (int) free_branches.size() &&
        branches[free_branches[start_equal]].a_from != branches[free_branches[start_equal + 1]].a_from
    ) {
        start_equal += 1;
    }
    if (start_equal + 1 >= (int) free_branches.size()) {
        // fail
        return false;
    }
    if (start_equal > 0) {
        // add in the part before they start being equal
        for (int i = 0; i < start_equal; i++) {
            if (curr.first.size() == 0 || branches[*curr.first.rbegin()].b_to == branches[free_branches[i]].a_from) {
                curr.first.push_back(free_branches[i]);
            } else {
                curr.second.push_back(free_branches[i]);
            }
        }
        all_combinations.push_back(curr);
        curr = {{},{}};
    }

    for (int i = start_equal; i < (int) free_branches.size(); i++) {
        // pass through every edge and assign it to one of the two parts,
        // keeping the matching parts together
        int first_end = curr.first.size() == 0 ? -1 : branches[*curr.first.rbegin()].b_to;
        int second_end = curr.second.size() == 0 ? -1 : branches[*curr.second.rbegin()].b_to;
        auto new_branch = branches[free_branches[i]];
        if (first_end == -1 || first_end == new_branch.a_from) {
            curr.first.push_back(free_branches[i]);
            first_end = new_branch.b_to;
        } else {
            assert(second_end == -1 || second_end == new_branch.a_from);
            curr.second.push_back(free_branches[i]);
            second_end = new_branch.b_to;
        }
        if (first_end == second_end) {
            all_combinations.push_back(curr);
            curr = {{},{}};
        }
    }

    if (!curr.first.empty()) {
        // add the remaining part
        all_combinations.push_back(curr);
        curr = {{},{}};
    }

    if (all_combinations.size() == 1) {
        // no repartition possible
        return false;
    }
    ll total_1 = 0, total_2 = 0;
    for (auto comb: all_combinations) {
        auto path_1 = comb.first;
        auto path_2 = comb.second;
        total_1 += combined_branches_length(path_1);
        total_2 += combined_branches_length(path_2);
    }
    ll delta = total_1 - total_2;

    ll improved = 1;
    while (improved) {
        // swap segments that improve the balance of the two paths
        improved = 0;
        for (auto &comb: all_combinations) {
            auto path_1 = comb.first;
            auto path_2 = comb.second;
            ll paths_delta = combined_branches_length(path_1) - combined_branches_length(path_2);
            ll new_delta = delta - 2 * paths_delta;
            if (abs(new_delta) >= abs(delta)) {
                continue ;
            }
            // swap
            swap(comb.first, comb.second);
            improved += abs(new_delta - delta);
            delta = new_delta;
            total_1 -= paths_delta;
            total_2 += paths_delta;
        }
    }

    if (abs(delta) == abs(p1.length - p2.length)) {
        // fail
        return false;
    }

    // reconstruct the paths, keep a reference to an edge on p1 and one on p2
    int p1_edge = all_combinations[0].first.size() > 0 ? all_combinations[0].first[0] : -1;
    int p2_edge = all_combinations[0].second.size() > 0 ? all_combinations[0].second[0] : -1;
    for (int i = 1; i < (int) all_combinations.size(); i++) {
        auto curr_comb = all_combinations[i];
        auto prev_comb = all_combinations[i - 1];

        if (!curr_comb.first.empty()) {
            int comb_first = curr_comb.first[0];
            if (p1_edge == -1) p1_edge = comb_first;
            if (path_prev[comb_first] != -1) {
                remove_prev(comb_first);
            }
        }
        if (!curr_comb.second.empty()) {
            int comb_first = curr_comb.second[0];
            if (p2_edge == -1) p2_edge = comb_first;
            if (path_prev[comb_first] != -1) {
                remove_prev(comb_first);
            }
        }

        if (!curr_comb.first.empty() && !prev_comb.first.empty()) {
            int comb_first = curr_comb.first[0];
            int comb_last = *prev_comb.first.rbegin();
            concat_edges(comb_last, comb_first);
        }
        if (!curr_comb.second.empty() && !prev_comb.second.empty()) {
            int comb_first = curr_comb.second[0];
            int comb_last = *prev_comb.second.rbegin();
            concat_edges(comb_last, comb_first);
        }
    }

    assert(p1_edge != -1 && p2_edge != -1);
    p1_edge = path_start(p1_edge), p2_edge = path_start(p2_edge);

    // update the set of paths
    assert(paths.erase(p1) == 1);
    assert(paths.erase(p2) == 1);
    paths.insert({ p1_edge, path_length_from(p1_edge) });
    paths.insert({ p2_edge, path_length_from(p2_edge) });
    return true;
}

unordered_set<int> find_possible_repartitions (int first_edge) {
    unordered_set<int> res;
    for (int edge = first_edge; edge != -1; edge = path_next[edge]) {
        // find an intersection at the end of this edge
        for (auto j: graph[branches[edge].a_from]) {
            int j_start = path_start(j);
            if (j_start == first_edge) {
                continue ;
            }
            res.insert(j_start);
        }
        for (auto j: backward_graph[branches[edge].b_to]) {
            int j_start = path_start(j);
            if (j_start == first_edge) {
                continue ;
            }
            res.insert(j_start);
        }
    }
    return res;
}

bool find_intersection (Path path) {
    // finds a simple intersection with a different path
    // that extends this path and keeps the other path above the shortest

    // start intersection, turn the end of a path into a new path
    // and concatenate the rest
    auto start_intersection = has_start_intersection(path);
    if (start_intersection.first != -1) {
        int j = start_intersection.first;
        int next_edge = path_next[j];
        assert(next_edge != -1);
        ll remaining_length = path_length_from(next_edge);
        assert (remaining_length > paths.begin()->length);

        // this swap is better
        int new_start = path_start(j);
        assert(paths.erase(path) == 1);
        assert(paths.erase(get_path(new_start)) == 1);
        remove_next(j);
        concat_edges(j, path.first);
        paths.insert({ next_edge, remaining_length });
        paths.insert({ new_start, path_length_from(new_start) });
        return true;
    }

    // intersection in the middle or at the end
    vector<int> edges = path_branches(path.first);
    random_shuffle(edges.begin(), edges.end());
    for (auto edge: edges) {
        // find an intersection at the end of this edge
        ll remaining_length_edge = path_length_from(path_next[edge]);
        for (auto j: graph[branches[edge].b_to]) {
            int j_start = path_start(j);
            if (j_start == path.first) {
                continue ;
            }
            ll j_length = path_length_from(j_start);
            ll remaining_length_j = path_length_from(j);
            ll new_length_j = j_length - remaining_length_j + remaining_length_edge;
            ll new_length = path.length - remaining_length_edge + remaining_length_j;
            if (new_length_j <= paths.begin()->length || new_length <= path.length) {
                // worse
                continue ;
            }

            // swap the remaining lengths for the two paths
            int j_prev = path_prev[j];
            int edge_next = path_next[edge];
            if(j_prev == -1) {
                // not sure what to do in this case...
                continue ;
            }
            assert(paths.erase(path) == 1);
            assert(paths.erase(get_path(j_start)) == 1);
            remove_prev(j);
            if (edge_next != -1) {
                remove_next(edge);
                concat_edges(j_prev, edge_next);
            }
            concat_edges(edge, j);
            assert(path_length_from(j_start) == new_length_j);
            assert(path_length_from(path.first) == new_length);
            paths.insert({ j_start, path_length_from(j_start) });
            paths.insert({ path.first, path_length_from(path.first) });
            return true;
        }
    }

    auto possible_repartitions = find_possible_repartitions(path.first);
    for (auto j: possible_repartitions) {
        ll j_length = path_length_from(j);
        ll delta = abs(j_length - path.length);
        if (delta <= 1) {
            continue ;
        }
        if (delta > 1 && find_repartition_2(path, get_path(j))) {
            return true;
        }
    }

    return false;
}

void rebalance_at (int branch_start) {
    // finds all the paths going forward and backward at branch_start
    // re-balances them in the most optimal way, combining the shortest
    // backward paths with the longest forward paths
    if (graph[branch_start].size() == 0) {
        return ;
    }
    vector<pair<ll, int>> forward_paths;
    vector<pair<ll, int>> backwards_path;
    for (auto i: backward_graph[branch_start]) {
        ll total_len = path_length_from(path_start(i));
        ll forward_len = path_length_from(path_next[i]);
        backwards_path.push_back({ total_len - forward_len, i });
        forward_paths.push_back({ forward_len, path_next[i] });
    }
    sort(forward_paths.begin(), forward_paths.end());
    sort(backwards_path.begin(), backwards_path.end());
    reverse(backwards_path.begin(), backwards_path.end());

    for (int i = 0; i < (int) forward_paths.size(); i++) {
        // combine longest forward and shortest backwards
        int backward = backwards_path[i].second;
        int forward = forward_paths[i].second;
        if (forward != -1 && path_prev[forward] != -1) {
            remove_prev(forward);
        }
        if (backward != -1 && path_next[backward] != -1) {
            remove_next(backward);
        }
        if (forward != -1 && backward != -1) {
            concat_edges(backward, forward);
        }
    }
}

void rebalance () {
    // try rebalancing at every possible junction
    for (int i = MAXN - 1; i >= 0; i--) {
        rebalance_at(i);
    }
    recompute_paths();
}

int main () {
    cin.tie(NULL);
    cout.tie(NULL);
    cerr.tie(NULL);
    ios_base::sync_with_stdio(false);
    set_timer();
    srand(1065);

    cin >> m_branches;
    bool solve_greedily = true;
    for (int i = 0; i < m_branches; i++) {
        branches[i].id = i;
        cin >> branches[i].a_from >> branches[i].b_to >> branches[i].length;
    }
    random_shuffle(branches, branches + m_branches);
    for (int i = 0; i < m_branches; i++) {
        if (!backward_graph[branches[i].b_to].empty()) {
            solve_greedily = false;
        }
        graph[branches[i].a_from].push_back(i);
        backward_graph[branches[i].b_to].push_back(i);
    }
    fill(path_next, path_next + m_branches, -1);
    fill(path_prev, path_prev + m_branches, -1);

    greedy_solution();
    if (solve_greedily) {
        // trees can be solved greedily
        cerr << "solved greedily\n";
        print_sol();
        return 0;
    }

    // the optimal solution if it's possible to make every path the same length
    ll optimal = 0;
    for (int i = 0; i < m_branches; i++) {
        optimal += branches[i].length;
    }
    optimal /= paths.size();

    vector<int> random_order(paths.size());
    for (int i = 0; i < (int) paths.size(); i++) {
        random_order[i] = i;
    }
    for (int attempt = 0; attempt < 10000 && !is_timeout(); attempt++) {
        // pick a few paths and try to change them at random
        int found_new_inters = 0;
        random_shuffle(random_order.begin(), random_order.end());
        for (auto i: random_order) {
            if (is_timeout()) {
                break ;
            }
            auto path_it = paths.begin();
            for (int j = 0; j < i; j++) {
                path_it++;
            }
            found_new_inters += find_intersection(*path_it);
            if (found_new_inters > sqrt(paths.size())) {
                break ;
            }
        }

        int help1 = 0, help2 = 0;
        while (!is_timeout() && find_intersection(*paths.begin())) {
            help1 += 1;
        };
        if (!is_timeout()) {
            rebalance();
        }
        while (!is_timeout() && find_intersection(*paths.begin())) {
            help2 += 1;
        };

        double optimal_dist = (double) abs(paths.begin()->length - optimal) * 100 / optimal;
        cerr << attempt << "\tRandom changes: " << found_new_inters << ", total help " << help1 << " + " << help2 << "\t";
        cerr << "Shortest: " << paths.begin()->length << "\tDistance from optimal: " << optimal_dist << "%\n";
    }

    print_sol();
}
