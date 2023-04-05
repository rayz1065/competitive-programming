#include <bits/stdc++.h>
#define TTTN 1000000000ll
#define MAXN 5005
#define MAXK 105

using namespace std;

typedef long long ll;

int n_nodes, k_players;
int strengths[MAXN];
bool adj_mat[MAXN][MAXN];
vector<int> graph[MAXN];

ll best_score;
vector<int> best_assignment;

chrono::_V2::system_clock::time_point start_time;

void set_timer () {
    start_time = chrono::high_resolution_clock::now();
}

bool is_timeout () {
    auto elapsed = chrono::high_resolution_clock::now() - start_time;
    ll milliseconds = chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    return milliseconds > 1750;
}

ll calc_score (vector<int> &assignment) {
    vector<ll> player_strengths(k_players, 0);
    vector<int> countries_count(k_players, 0);
    for (int i = 0; i < assignment.size(); i++) {
        int player = assignment[i];
        player_strengths[player] += strengths[i];
        countries_count[player] += 1;
    }
    sort(countries_count.begin(), countries_count.end());
    sort(player_strengths.begin(), player_strengths.end());

    ll hi_dev = countries_count[k_players - 1] * TTTN,
       lo_dev = countries_count[0] * TTTN;
    ll hi_str = player_strengths[k_players - 1],
        lo_str = player_strengths[0];
    return hi_dev - lo_dev + hi_str - lo_str;
}

vector<int> assignment;
vector<ll> player_strengths;
vector<int> countries_count;

void reassign_country (int i, int player_new) {
    int player = assignment[i];
    assignment[i] = player_new;
    countries_count[player_new] += 1;
    countries_count[player] -= 1;
    player_strengths[player_new] += strengths[i];
    player_strengths[player] -= strengths[i];
}

void swap_assignment (int i, int j) {
    int player_i = assignment[i];
    int player_j = assignment[j];
    swap(assignment[i], assignment[j]);
    ll delta = strengths[i] - strengths[j];
    player_strengths[player_i] -= delta;
    player_strengths[player_j] += delta;
}

void print_best_assignment () {
    auto countries_minmax = minmax_element(countries_count.begin(), countries_count.end());
    int countries_diff = *countries_minmax.second - *countries_minmax.first;
    cerr << calc_score(best_assignment)
         << ", countries_diff = " << countries_diff << "\n";
    for (auto j: best_assignment) {
        cout << j << " ";
    }
    cout << "\n";
    // for (int i = 0; i < n_nodes; i++) {
    //     for (auto j: graph[i]) {
    //         assert(assignment[i] != assignment[j]);
    //     }
    // }
}

ll calc_curr_score () {
    auto dev = minmax_element(countries_count.begin(), countries_count.end());
    auto str = minmax_element(player_strengths.begin(), player_strengths.end());
    ll hi_dev = *dev.second * TTTN,
       lo_dev = *dev.first * TTTN;
    ll hi_str = *str.second,
        lo_str = *str.first;
    return hi_dev - lo_dev + hi_str - lo_str;
}

bool countries_count_heuristic (int i, int j) {
    return countries_count[i] < countries_count[j];
}

vector<int> calc_player_neigh (int node) {
    vector<int> player_neigh(k_players, false);
    for (auto j: graph[node]) {
        if (j < assignment.size()) {
            player_neigh[assignment[j]] += 1;
        }
    }
    return player_neigh;
}

bool valid_swap (int a, int b, vector<int> &a_neigh, vector<int> &b_neigh) {
    int player_a = assignment[a], player_b = assignment[b];
    return a_neigh[player_b] - adj_mat[a][b] <= 0 && b_neigh[player_a] - adj_mat[a][b] <= 0;
}

bool rebalance_countries () {
    // balance the countries
    int target_countries_count = n_nodes / k_players;
    set<int> too_few_countries;
    for (int i = 0; i < k_players; i++) {
        if (countries_count[i] < target_countries_count) {
            too_few_countries.insert(i);
        }
    }
    for (int i = 0; i < n_nodes; i++) {
        int player = assignment[i];
        if (countries_count[player] <= target_countries_count) {
            continue ;
        }
        auto player_neigh = calc_player_neigh(i);
        for (auto player_new: too_few_countries) {
            if (player_neigh[player_new]) {
                continue ;
            }
            reassign_country(i, player_new);
            if (countries_count[player_new] >= target_countries_count) {
                too_few_countries.erase(player_new);
            }
            break ;
        }
    }
    return too_few_countries.empty();
}

bool rebalance_strength () {
    ll improvement = 0;
    for (int i = 0; i < n_nodes; i++) {
        int player_i = assignment[i];
        auto neigh_i = calc_player_neigh(i);
        for (int j = i + 1; j < n_nodes && !is_timeout(); j++) {
            // should I swap these?
            int player_j = assignment[j];
            ll str_curr = abs(player_strengths[player_i] - player_strengths[player_j]);
            ll delta = strengths[i] - strengths[j];
            ll str_new = abs(player_strengths[player_i] - player_strengths[player_j] - 2 * delta);
            if (str_new > str_curr) {
                // no improvement
                continue ;
            }
            auto neigh_j = calc_player_neigh(j);
            if (!valid_swap(i, j, neigh_i, neigh_j)) {
                // illegal assignment
                continue ;
            }
            improvement += str_curr - str_new;
            swap_assignment(i, j);

            player_i = assignment[i];
            neigh_i = calc_player_neigh(i);
        }
    }
    cerr << improvement << "\n";
    return improvement;
}

int random_swaps () {
    int swaps = 0;
    while (swaps < 10 && !is_timeout()) {
        int i = rand() % n_nodes;
        int j = rand() % (n_nodes - 1);
        if (j >= i) {
            j += 1;
        }
        int player_i = assignment[i];
        int player_j = assignment[j];
        if (player_i == player_j) {
            continue ;
        }
        auto neigh_i = calc_player_neigh(i);
        auto neigh_j = calc_player_neigh(j);
        if (!valid_swap(i, j, neigh_i, neigh_j)) {
            // illegal assignment
            continue ;
        }
        swaps += 1;
        if (rand() % 2 && countries_count[player_i] != countries_count[player_j]) {
            if (countries_count[player_i] > countries_count[player_j]) {
                reassign_country(i, player_j);
            } else {
                reassign_country(j, player_i);
            }
        }
        swap_assignment(i, j);
    }
    return swaps;
}

void store_improvements() {
    ll score = calc_curr_score();
    if (score < best_score) {
        best_score = score;
        best_assignment = assignment;
    }
}

void optimize_assignment () {
    for (int epoch = 0; epoch < 50 && !rebalance_countries(); epoch++);

    while(!is_timeout()) {
        while (rebalance_strength());
        store_improvements();
        random_swaps();
    }
}

void solve () {
    if (is_timeout()) {
        print_best_assignment();
        exit(0);
    }
    if (assignment.size() == n_nodes) {
        ll score = calc_curr_score();
        best_score = score;
        best_assignment = assignment;
        optimize_assignment();
        print_best_assignment();
        exit(0);
        // if (best_assignment.size() == 0 || score < best_score) {
        //     best_assignment = assignment;
        //     best_score = score;
        //     cerr << best_score << "\n";
        // }
        return ;
    }

    int node = assignment.size();
    auto player_neigh = calc_player_neigh(node);
    vector<int> priorities;
    for (int player = 0; player < k_players; player++) {
        if (player_neigh[player]) {
            continue ;
        }
        priorities.push_back(player);
    }
    sort(priorities.begin(), priorities.end(), countries_count_heuristic);
    for (int p = 0; p < priorities.size(); p++) {
        auto player = priorities[p];
        assignment.push_back(player);
        player_strengths[player] += strengths[node];
        countries_count[player] += 1;
        solve();
        countries_count[player] -= 1;
        player_strengths[player] -= strengths[node];
        assignment.pop_back();
    }
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    set_timer();
    cin >> n_nodes >> k_players;
    for (int i = 0; i < n_nodes; i++) {
        cin >> strengths[i];
    }
    for (int i = 0; i < n_nodes; i++) {
        int l;
        cin >> l;
        while(l--) {
            int v;
            cin >> v;
            graph[i].push_back(v);
            adj_mat[i][v] = true;
        }
    }

    player_strengths.resize(k_players, 0);
    countries_count.resize(k_players, 0);
    solve();
    print_best_assignment();
}
