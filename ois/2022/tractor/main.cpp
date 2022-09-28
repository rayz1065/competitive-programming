#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#define MAXN 100005
using namespace std;

chrono::_V2::system_clock::time_point start_time;

int n, k;
vector<int> graph[MAXN];

set<int> missing;
vector<int> curr;
vector<int> best_sol;
int curr_cost;
int best_cost;
int curr_slack;
int best_slack;

void print_best_solution () {
    cout << best_cost << "\n";
    for (auto j: best_sol) {
        cout << j << " ";
    }
    cout << "\n";
}

int timeout_acc;
bool is_timeout () {
#ifdef DEBUG
    return false;
#endif
    if ((++timeout_acc % 10000) != 0) {
        return false;
    }
    auto elapsed = chrono::high_resolution_clock::now() - start_time;
    long long milliseconds = chrono::duration_cast<std::chrono::milliseconds>(
            elapsed).count();
    return milliseconds > 9500;
}

bool should_cut () {
    if (curr_cost >= best_cost || curr_slack >= best_slack) {
        return true;
    } else if (missing.size() == 0) {
        // better solution found
        return false;
    }
    int node = curr.back();
    int leftmost = *missing.begin();
    int rightmost = *missing.rbegin();
    int dist_to_left = node - leftmost;
    int dist_to_right = rightmost - node;
    int estimate_1 = curr_cost + dist_to_left * 2 + dist_to_right;
    int estimate_2 = curr_cost + dist_to_left + dist_to_right * 2;

    // TODO replace with >=
    return min(estimate_1, estimate_2) >= best_cost;
}

void solve_1 () {
    if (is_timeout()) {
        print_best_solution();
        exit(0);
    }
    if (should_cut()) {
        // no improvements
        return ;
    }
    if (curr.size() == n) {
        best_sol = curr;
        best_cost = curr_cost;
        best_slack = curr_slack;
#ifdef DEBUG
        print_best_solution();
#endif
        return ;
    }

    int node = curr[curr.size() - 1];
    for (auto j: graph[node]) {
        if (missing.find(j) != missing.end()) {
            curr.push_back(j);
            missing.erase(j);
            curr_cost += abs(node - j);
            curr_slack += abs(node - j) - k;

            solve_1();

            curr.pop_back();
            missing.insert(j);
            curr_cost -= abs(node - j);
            curr_slack -= abs(node - j) - k;
        }
    }
}

/**
 * Finds the best solution
 */
void no_brainer_1 () {
    // creates the graph explicitly
    // for (int dist = k; dist < n; dist++) {
    //     for (int i = 0; i < n; i++) {
    //         int bef = i - dist, aft = i + dist;
    //         if (bef >= 0) {
    //             graph[i].push_back(bef);
    //         }
    //         if (aft < n) {
    //             graph[i].push_back(aft);
    //         }
    //         solve_1();
    //     }
    // }

    for (int i = 0; i < n; i++) {
        int start = max(i - 2 * k, 0);
        for (int j = start; j <= i - k; j++) {
            graph[i].push_back(j);
            graph[j].push_back(i);
        }
    }
    for (int i = 1; i < n; i++) {
        missing.insert(i);
    }
    curr.push_back(0);
    solve_1();
}

/**
 * Approximates the solution with a smaller graph
 */
void no_brainer_2 () {
    int mid_start = 2 * k;
    int mid_start_end = mid_start + k - 1;
    int mid_end_start = (n - (n % k)) - 3 * k;
    int mid_end = mid_end_start + k - 1;
    if (mid_start_end > mid_end_start) {
        return no_brainer_1();
    }
    cout << "instead of " << n << " use " << n - (mid_end_start - mid_start_end) + 1 << "\n";
    int true_n = n;
    n = n - (mid_end_start - mid_start_end) + 1;
    no_brainer_1();
    n = true_n;
    vector<int> full_sol = { 0 };
    set<int> paths_mod_used;
    int real_cost = 0;
    for (int i = 1; i < best_sol.size(); i++) {
        int next_node = best_sol[i];
        if (next_node > mid_start_end) {
            next_node += mid_end_start;
        }
        int curr_node = full_sol[full_sol.size() - 1];
        cout << "From " << curr_node << " to " << next_node << "\n";
        full_sol.push_back(next_node);
    }
}

void add_between (int start, int limit) {
    int mul = start < limit ? +1 : -1;
    // cout << "Adding between " << start << " and " << limit << "\n";

    for (int i = start; i * mul < limit * mul; i += k * mul) {
        if (i == 0) {
            continue ;
        }
        int node = *curr.rbegin();
        curr.push_back(i);
        curr_cost += abs(i - node);
    }
}

void no_brainer_3 () {
    curr.push_back(0);
    int groups_count = n / k + (n % k > 0);
    int last_group_start = (groups_count - 1) * k;
    // cout << "There are " << groups_count << " groups\n";
    // cout << "Last group starts at " << last_group_start << "\n";
    for (int j = 0; j < k; j++) {
        // move backwards on odd ones
        int start = j;
        int limit = n;
        int mul = +1;
        if (j % 2 == 1) {
            start = last_group_start + j;
            mul = -1;
            limit = -1;
            if (start >= n) {
                start -= k;
            }
        }
        int node = *curr.rbegin();
        int ideal_start = start; // we can't always start from here
        while (abs(node - start) < k) {
            start += k * mul;
        }
        // cout << "\nStart from " << start << " instead of " << ideal_start << ", end at " << limit << "\n";
        add_between(start, ideal_start - mul);
        add_between(start + k * mul, limit);
    }
    if (curr_cost < best_cost) {
        best_cost = curr_cost;
        best_sol = curr;
    }

    curr.clear();
    curr_cost = 0;
}

int main () {
    start_time = chrono::high_resolution_clock::now();

    cin >> n >> k;
    best_cost = INT_MAX >> 1;
    best_slack = INT_MAX >> 1;
    if (n > 3 * k) {
        no_brainer_3();
    }
    if (n <= 10000) {
        no_brainer_1();
    }
    // no_brainer_2();
    print_best_solution();
}
