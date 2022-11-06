#include <bits/stdc++.h>
#ifndef DEBUG
#pragma GCC optimize("O3")
#endif
#define MAXN 105

using namespace std;

int n;
int sat[MAXN][MAXN];
bool assigned[MAXN];
int tot_sol_found = 0;

vector<int> best_sol;

chrono::_V2::system_clock::time_point start_time;

void solve (int i, vector<int> &curr);

int timeout_acc;
bool is_timeout () {
    if ((++timeout_acc % 100) != 0) {
        return false;
    }
    auto elapsed = chrono::high_resolution_clock::now() - start_time;
    long long milliseconds = chrono::duration_cast<std::chrono::milliseconds>(
            elapsed).count();
    return milliseconds > 2950;
}

int calc_score (vector<int> &sol) {
    int s = 0;
    for (int i = 0; i < sol.size(); i++) {
        if (sol[i] != -1) s += sat[i][sol[i]];
    }
    return s;
}

void store_sol (vector<int> &sol) {
    if (best_sol.size() == 0 || calc_score(sol) < calc_score(best_sol)) {
#ifdef DEBUG
        tot_sol_found++;
        cout << "sol #" << tot_sol_found << ": " << calc_score(sol) << "\n";
#endif
        best_sol = sol;
    }
}

void print_best_sol () {
#ifdef DEBUG
    cout << calc_score(best_sol) << "\n";
#endif
    for (int i = 0; i < n; i++) {
        cout << best_sol[i] << " \n"[i + 1 == n];
    }
}

bool valid_trade (int i, int j, int i2, int j2) {
    if (j == -1 || j2 == -1) return false;
    return (sat[i][j2] > sat[i][j] &&  // i prefers j2 over j
            sat[i2][j] > sat[i2][j2]); // i2 prefers j over j2
}

bool is_tradable (int i, int j, vector<int> &curr) {
    for (int i2 = 0; i2 < curr.size(); i2++) {
        int j2 = curr[i2];
        if (valid_trade(i, j, i2, j2)) {
            return true;
        }
    }
    return false;
}

int compute_trades (vector<int> &assignments, vector<int> &trade_order) {
    bool found = true;
    int trades_count = 0;
    while (found) {
        found = false;
        for (int k = 0; k < trade_order.size(); k++) {
            int i = trade_order[k];
            int j = assignments[i];
            for (int k2 = k + 1; k2 < trade_order.size(); k2++) {
                int i2 = trade_order[k2];
                int j2 = assignments[i2];
                if (valid_trade(i, j, i2, j2)) {
                    swap(assignments[i], assignments[i2]);
                    found = true;
                    trades_count++;
                }
            }
        }
    }
    return trades_count;
}

bool prune (int i, vector<int> &curr) {
    if (i < 5) {
        return false;
    }
    int score = calc_score(curr);
    if (score >= calc_score(best_sol)) {
        // not an improvement
        return true;
    }

    int is_wanted[n];
    int wanted_by[n];
    int single_wanted_gift[n];
    fill(is_wanted, is_wanted + n, 0);
    fill(single_wanted_gift, single_wanted_gift + n, -1);
    for (int i2 = i; i2 < n; i2++) {
        // can I find a gift for this person?
        if (curr[i2] != -1) {
            continue ;
        }
        int worst = INT_MAX >> 1;
        int found = 0;
        int found_g;
        for (int j = 0; j < n; j++) {
            if (!assigned[j] && !is_tradable(i2, j, curr)) {
                worst = min(worst, sat[i2][j]);
                is_wanted[j]++;
                wanted_by[j] = i2;
                found++;
                found_g = j;
            }
        }
        if (!found) {
            return true;
        }
        score += worst;
        single_wanted_gift[i2] = found == 1 ? found_g : -1;
    }
    for (int j = 0; j < n; j++) {
        if (!is_wanted[j] && !assigned[j]) {
            return true;
        }
    }
    if (score >= calc_score(best_sol)) {
        // not an improvement
        return true;
    }
    for (int i2 = i; i2 < n; i2++) {
        if (single_wanted_gift[i2] != -1) {
            curr[i2] = single_wanted_gift[i2];
            assigned[single_wanted_gift[i2]] = true;
            solve(i, curr);
            assigned[single_wanted_gift[i2]] = false;
            curr[i2] = -1;
            return true;
        }
    }
    for (int j = 0; j < n; j++) {
        if (is_wanted[j] == 1) {
            curr[wanted_by[j]] = j;
            assigned[j] = true;
            solve(i, curr);
            assigned[j] = false;
            curr[wanted_by[j]] = -1;
            return true;
        }
    }
    return false;
}

void solve (int i, vector<int> &curr) {
    if (is_timeout()) {
        print_best_sol();
        exit(0);
    }
    if (i == n) {
        store_sol(curr);
        return ;
    }
    if (curr[i] != -1) {
        return solve(i + 1, curr);
    }
    if (prune(i, curr)) {
        return ;
    }

    for (int j = 0; j < n; j++) {
        if (!assigned[j] && !is_tradable(i, j, curr)) {
            curr[i] = j;
            assigned[j] = true;
            solve(i + 1, curr);
            assigned[j] = false;
            curr[i] = -1;
        }
    }
}

vector<int> random_sol () {
    vector<int> sol;
    for (int i = 0; i < n; i++) {
        sol.push_back(i);
    }
    random_shuffle(sol.begin(), sol.end());
    vector<int> trade_order;
    for (int i = 0; i < n; i++) {
        trade_order.push_back(i);
    }
    random_shuffle(trade_order.begin(), trade_order.end());
    compute_trades(sol, trade_order);
    return sol;
}

int main () {
    start_time = chrono::high_resolution_clock::now();
    srand(1065);
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#endif
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> sat[i][j];
        }
    }

    for (int i = 0; i < 100; i++) {
        vector<int> sol = random_sol();
        store_sol(sol);
    }
    vector<int> curr(n, -1);
    solve(0, curr);
    print_best_sol();
}
