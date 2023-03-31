#include <bits/stdc++.h>
#define DIGITS 10
#define MAXN 100005

using namespace std;

int n;
int numbers[MAXN];
int swaps_by_type[DIGITS][DIGITS];

inline int apply_swap (int digit, int swap_a, int swap_b) {
    if (digit == swap_a) return swap_b;
    if (digit == swap_b) return swap_a;
    return digit;
}

int move_cost (int from, int to, int swap_a, int swap_b) {
    from = apply_swap(from, swap_a, swap_b);
    to = apply_swap(to, swap_a, swap_b);
    return abs(from - to);
}

int calc_cost (int swap_a, int swap_b) {
    int s = 0;
    for (int i = 0; i < DIGITS; i++) {
        for (int j = i + 1; j < DIGITS; j++) {
            s += swaps_by_type[i][j] * move_cost(i, j, swap_a, swap_b);
        }
    }
    return s;
}

int best_swap (int i) {
    // tries any possible swap and calculates the score of the best one
    int best = INT_MAX >> 1;
    for (int swap_a = 0; swap_a < DIGITS; swap_a++) {
        for (int swap_b = swap_a + 1; swap_b < DIGITS; swap_b++) {
            int cost = calc_cost(swap_a, swap_b);
            // add the cost for the first move
            cost += abs(numbers[i - 1] - apply_swap(numbers[i], swap_a, swap_b));
            best = min(best, cost);
        }
    }
    return best;
}

int tc () {
    string s_numbers;
    cin >> s_numbers;
    n = s_numbers.length() + 1;
    numbers[0] = 0;
    for (int i = 0; i < s_numbers.length(); i++) {
        numbers[i + 1] = s_numbers[i] - '0';
    }
    for (int i = 0; i < DIGITS; i++) {
        fill(swaps_by_type[i], swaps_by_type[i] + DIGITS, 0);
    }
    for (int i = 1; i < n; i++) {
        int prev_digit = numbers[i - 1];
        int curr_digit = numbers[i];
        if (prev_digit > curr_digit) swap(prev_digit, curr_digit);
        swaps_by_type[prev_digit][curr_digit] += 1;
    }

    int s = 0, best = calc_cost(0, 0);
    for (int i = 1; i < n; i++) {
        int prev_digit = numbers[i - 1];
        int curr_digit = numbers[i];
        if (prev_digit > curr_digit) swap(prev_digit, curr_digit);
        swaps_by_type[prev_digit][curr_digit] -= 1;
        best = min(best, best_swap(i) + s);
        s += move_cost(prev_digit, curr_digit, 0, 0);
    }

    return best;
}

int main () {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) cout << tc() << "\n";
}
