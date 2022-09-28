#include <bits/stdc++.h>
#define MAXM 305
#pragma GCC optimize("O3")
using namespace std;

int a, b;
long long int k;

long long int memo_map[MAXM][MAXM][MAXM];
int power_10[MAXM];

void store (int remaining_b, int remaining_digits, int curr_modulo, long long int val) {
    memo_map[remaining_b][remaining_digits][curr_modulo] = val + 1;
}

long long int get (int remaining_b, int remaining_digits, int curr_modulo) {
    return memo_map[remaining_b][remaining_digits][curr_modulo] - 1;
}

long long int count_numbers (int remaining_b, int remaining_digits, int curr_modulo) {
    if (remaining_digits > remaining_b || remaining_digits * 9 < remaining_b) {
        // can't create such a number
        return 0;
    }
    if (remaining_digits == 0) {
        return (remaining_b == 0 && curr_modulo == 0) ? 1 : 0;
    }
    if (memo_map[remaining_b][remaining_digits][curr_modulo]) {
        return get(remaining_b, remaining_digits, curr_modulo);
    }
    // sum for every possible digit
    long long int s = 0;
    for (int i = 1; i <= min(9, remaining_b); i++) {
        int next_mod = (curr_modulo + (power_10[remaining_digits - 1]) * i) % a;
        s += count_numbers(remaining_b - i, remaining_digits - 1, next_mod);
    }
    store(remaining_b, remaining_digits, curr_modulo, s);
    return s;
}

int calculate_modulo (vector<int> curr) {
    int s = 0;
    for (int i = 0; i < curr.size(); i++) {
        s = ((s * 10) + curr[i]) % a;
    }
    return s;
}

int calculate_sum (vector<int> curr) {
    int s = 0;
    for (int i = curr.size() - 1; i >= 0; i--) {
        s+= curr[i];
    }
    return s;
}

int main () {
    cin >> a >> b >> k;
    power_10[0] = 1;
    for (int i = 1; i < MAXM; i++) {
        power_10[i] = (power_10[i - 1] * 10) % a;
    }

    long long int left_k = 0;
    // determine the number of required digits
    int digits = 0;
    while (digits <= b) {
        long long int delta = count_numbers(b, digits, 0);
        // cout << "With " << digits << " digits there are " << delta << " numbers\n";
        if (left_k + delta <= k - 1) {
            left_k += delta;
            if (digits == b) {
                break ;
            }
            digits ++;
        }
        else {
            break ;
        }
    }

    // cout << a << " " << b << " " << k << "\n";
    // cout << "The solution has " << digits << " digits\n";
    vector<int> curr(digits, 0);
    for (int found_digits = 0; found_digits < digits; found_digits++) {
        int remaining_digits = digits - found_digits - 1;
        int curr_modulo = calculate_modulo(curr);
        int remaining_b = b - calculate_sum(curr);
        int next_digit = 1;
        // cout << "Found " << found_digits << ", mod " << curr_modulo << ", rem " << remaining_b << "\n";
        while (next_digit <= min(9, remaining_b)) {
            long long int delta = count_numbers(remaining_b - next_digit,
                digits - found_digits - 1,
                (curr_modulo + (power_10[remaining_digits]) * next_digit) % a);
            if (left_k + delta > k - 1) {
                break ;
            }
            left_k += delta;
            if (next_digit == 9) {
                break ;
            }
            next_digit++;
        }
        curr[found_digits] = next_digit;
    }

    for (auto i: curr) {
        cout << i;
    }
    cout << "\n";
}
