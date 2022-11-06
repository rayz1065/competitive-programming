#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 100005
#define MAXP 1000005

using namespace std;

int n, numbers[MAXN];
int b_start_price, p_prime_bonus, d_digits_cost[10];

bool is_prime[MAXP];
int primes[] = { 2, 3, 5, 7 };
typedef long long ll;

void era (int maxp) {
    fill(is_prime + 2, is_prime + maxp, true);
    for (int i = 2; i < maxp; i++) {
        if (is_prime[i]) {
            for (ll j = (ll) i * i; j < maxp; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int calc_cost (int label) {
    int s = b_start_price;
    if (is_prime[label]) s += p_prime_bonus + label;
    int digits_sum = 0, digits_prod = 1;
    for (int tmp = label; tmp > 0; tmp /= 10) {
        int dig = tmp % 10;
        s += d_digits_cost[dig];
        digits_sum += dig;
        digits_prod *= dig;
    }
    if (is_prime[digits_sum]) s += digits_sum;
    if (is_prime[digits_prod]) s += digits_prod;
    return s;
}

int unsplit (int split[], int digits_count) {
    int s = 0;
    for (int i = digits_count - 1; i >= 0; i--) {
        s = s * 10 + split[i];
    }
    return s;
}

int best_alt_cost (int label) {
    int split[10] = {}, digits_count = 0;
    for (int tmp = label; tmp > 0; tmp /= 10) {
        split[digits_count++] = tmp % 10;
    }
    int s = 0;
    for (int i = 0; i < digits_count; i++) {
        int digit_memo = split[i];
        for (int j = (i + 1 == digits_count); j <= 9; j++) {
            split[i] = j;
            int unsp = unsplit(split, digits_count);
            s = max(s, calc_cost(unsp));
            // cout << label << " " << unsp << " -> " << calc_cost(unsp) << "\n";
        }
        split[i] = digit_memo;
    }
    return s;
}

long long solve () {
    long long s = 0;
    for (int i = 0; i < n; i++) {
        s += best_alt_cost(numbers[i]);
    }
    return s;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    cin >> b_start_price >> p_prime_bonus;
    era(MAXP);
    for (int i = 0; i < 4; i++) {
        cin >> d_digits_cost[primes[i]];
    }
    cout << solve() << "\n";
}