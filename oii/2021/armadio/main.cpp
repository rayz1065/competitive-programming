#include <bits/stdc++.h>
#define MAXN 4000005

using namespace std;

bool is_prime[MAXN];
bool is_searched[MAXN];
// vector<int> primes;
vector<int> prime_divisors[MAXN];
int first_divisor[MAXN];
int solution[MAXN];
int totient_memo[MAXN];

void era () {
    fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            // find solution
            // primes.push_back(i);
            first_divisor[i] = i;
            if (is_searched[i]) {
                prime_divisors[i].push_back(i);
            }
            for (int j = i + i; j < MAXN; j+= i) {
                // find solution
                is_prime[j] = false;
                if (is_searched[j]) {
                    prime_divisors[j].push_back(i);
                }
                if (first_divisor[j] == 0) {
                    first_divisor[j] = i;
                }
            }
        }
    }
}

void _get_divisors (int n, int i, int curr, vector<int> &divisors) {
    if (i == prime_divisors[n].size()) {
        // no more to find
        divisors.push_back(curr);
        return ;
    }
    for (int am = 0; n % curr == 0; am++) {
        _get_divisors(n, i + 1, curr, divisors);
        curr *= prime_divisors[n][i];
    }
}

vector<int> get_divisors (int n) {
    vector<int> divisors;
    _get_divisors(n, 0, 1, divisors);
    return divisors;
}

/**
 * The euler totient function finds integers less than n which are
 * coprime with n
 */
int euler_totient (int n) {
    if (n <= 1) {
        return 0;
    }
    if (totient_memo[n] != 0) {
        return totient_memo[n];
    }
    // find coprime (a, b) that multiply to n
    int a = n;
    while (a % first_divisor[n] == 0) {
        a /= first_divisor[n];
    }
    int b = n / a;
    if (a == 1) {
        return totient_memo[n] = n / first_divisor[n] * (first_divisor[n] - 1);
    }
    return totient_memo[n] = euler_totient(a) * euler_totient(b);
}

/**
 * How many pairs of coprime numbers (a, b) sum up to n?
 */
int count_coprime_sums (int n) {
    return euler_totient(n);
}

/**
 * How many pairs of numbers (a, b) have a + b + gcd(a, b) = n
 */
int solve (int n) {
    vector<int> divisors = get_divisors(n);
    int s = 0;
    for (auto j: divisors) {
        s += count_coprime_sums(j - 1);
    }
    return s;
}

void evadi(int Q, vector<int>& N) {
    for (auto num: N) {
        is_searched[num] = true;
    }
    era();
    for (int i = 0; i < Q; i++) {
        N[i] = solve(N[i]);
    }
}
