#include <bits/stdc++.h>
#define MAXN 20005

using namespace std;

int n;
int exercises[MAXN], first_tiring_ex;
bool used[MAXN];
vector<int> best_sol;

int calc_score () {
    int s = 0, worst_s = 0;
    for (int i = 0; i < n; i++) {
        s = max(0, s + exercises[i]);
        worst_s = max(s, worst_s);
    }
    return worst_s;
}

int solve_small () {
    // solves for N <= 10
    sort(exercises, exercises + n);
    int best_score = calc_score();
    best_sol = vector<int>(exercises, exercises + n);
    while (next_permutation(exercises, exercises + n)) {
        int score = calc_score();
        if (score < best_score) {
            best_score = score;
            best_sol = vector<int>(exercises, exercises + n);
        }
    }
    return best_score;
}

bool find_sol (int score) {
    // find a solution with this score
    vector<int> s;
    int curr_score = 0;
    int rel_l = 0, rel_r = first_tiring_ex - 1;
    int work_l = first_tiring_ex, work_r = n - 1;
    int slack = 0;
    while (rel_l <= rel_r && work_l <= work_r) {
        if (curr_score + exercises[work_r] <= score) { // hardest
            s.push_back(exercises[work_r]), curr_score += exercises[work_r];
            work_r--;
        } else if (curr_score + exercises[rel_l] >= -slack) { // most relaxing
            s.push_back(exercises[rel_l]), curr_score = max(0, curr_score + exercises[rel_l]);
            rel_l++;
        } else if (curr_score + exercises[work_l] <= score) { // easiest
            s.push_back(exercises[work_l]), curr_score += exercises[work_l];
            work_l++;
        } else { // least relaxing
            s.push_back(exercises[rel_r]), curr_score = max(0, curr_score + exercises[rel_r]);
            rel_r--;
        }
    }
    while (rel_l <= rel_r) {
        s.push_back(exercises[rel_l]), curr_score += exercises[rel_l];
        rel_l++;
    }
    while (work_l <= work_r) {
        s.push_back(exercises[work_l]), curr_score += exercises[work_l];
        work_l++;
    }
    if (curr_score > score) {
        return false;
    }
    best_sol = s;
    return true;
}

bool find_sol_slow (int score) {
    fill(used, used + n, false);
    vector<int> s;
    int rel_l = 0, rel_r = first_tiring_ex - 1;
    int work_l = first_tiring_ex, work_r = n - 1;
    int curr_score = 0;
    int slack = 0;
    while (rel_l <= rel_r && work_l <= work_r) {
        if (used[rel_r]) {
            rel_r--;
        } else if (used[work_l]) {
            work_l++;
        } else if (used[work_r]) {
            work_r--;
        } else if (used[rel_l]) {
            rel_l++;
        } else if (curr_score + exercises[work_r] <= score) { // hardest
            s.push_back(exercises[work_r]), curr_score += exercises[work_r];
            work_r--;
        } else if (curr_score + exercises[rel_l] >= -slack) { // most relaxing
            s.push_back(exercises[rel_l]), curr_score = max(0, curr_score + exercises[rel_l]);
            rel_l++;
        } else {
            // find the most ideal one
            int best_fit = INT_MAX >> 1, best = -1;
            for (int i = rel_l; i <= rel_r; i++) {
                if (used[i]) {
                    continue ;
                }
                int new_score = abs(0 - (curr_score + exercises[i]));
                if (new_score < best_fit) {
                    best_fit = new_score, best = i;
                }
            }
            for (int i = work_l; i <= work_r; i++) {
                if (used[i] || curr_score + exercises[i] > score) {
                    continue ; // not an option
                }
                int new_score = abs(score - (curr_score + exercises[i]));
                if (new_score < best_fit) {
                    best_fit = new_score, best = i;
                }
            }
            // cout << "best fit for " << curr_score << " to get closer to 0 or " << score << " is " << exercises[best] << " -> " << best_fit << "\n";
            s.push_back(exercises[best]), curr_score = max(0, curr_score + exercises[best]);
            used[best] = true;
        }
    }
    while (rel_l <= rel_r) {
        if (!used[rel_l]) {
            s.push_back(exercises[rel_l]), curr_score += exercises[rel_l];
        }
        rel_l++;
    }
    while (work_l <= work_r) {
        if (!used[work_l]) {
            s.push_back(exercises[work_l]), curr_score += exercises[work_l];
        }
        work_l++;
    }
    if (curr_score > score) {
        return false;
    }
    best_sol = s;
    return true;
}

int solve () {
    if (n <= 10) {
        return solve_small();
    }
    first_tiring_ex = upper_bound(exercises, exercises + n, 0) - exercises;
    int l = exercises[n - 1], r = calc_score();
    int sol = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (find_sol_slow(mid)) {
            sol = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return sol;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> exercises[i];
    }
    sort(exercises, exercises + n);
    cout << solve() << "\n";
    for (auto i: best_sol) {
        cout << i << " ";
    }
    cout << "\n";
}
