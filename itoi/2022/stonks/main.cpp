#include <bits/stdc++.h>
#pragma GCC optimize("O3")

#define MAXN 3005
#define MAXK 3005

using namespace std;

void fastin (int &v) {
    v = 0;
    char c = getchar_unlocked();
    while (c < '0') {
        c = getchar_unlocked();
    }
    for (; c >= '0'; c = getchar_unlocked()) {
        v = v * 10 + c - '0';
    }
}

// input data
int n_days, k_stocks;
int buy_on_day[MAXN][MAXK];
int sell_on_day[MAXN][MAXK];
double memo[MAXN][MAXK];
double max_day_yield[MAXN];

void calculate_max_next_yield (int day) {
    double max_yield = 0.;

    // sell and buy something else
    for (int j = 0; j < k_stocks; j++) {
        max_yield = max(max_yield, memo[day + 1][j] / buy_on_day[day][j]);
    }

    max_day_yield[day] = max_yield;
}

void calculate_yield (int day, int owned_stock) {
    // sell everything and buy nothing else
    double money = sell_on_day[day][owned_stock];
    double max_yield = money;

    // don't sell yet
    max_yield = max(max_yield, memo[day + 1][owned_stock]);

    // sell and buy something else
    max_yield = max(max_yield, max_day_yield[day] * money);

    memo[day][owned_stock] = max_yield;
}

int main () {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    fastin(n_days);
    fastin(k_stocks);

    k_stocks += 1;
    for (int i = 0; i < n_days; i++) {
        for (int j = 0; j < k_stocks - 1; j++) {
            fastin(buy_on_day[i][j]);
            fastin(sell_on_day[i][j]);
        }
        buy_on_day[i][k_stocks - 1] = 1;
        sell_on_day[i][k_stocks - 1] = 1;
    }

    for (int stock = 0; stock < k_stocks; stock++) {
        // the yield for the last day is the value of the stock
        memo[n_days - 1][stock] = sell_on_day[n_days - 1][stock];
    }
    for (int day = n_days - 2; day >= 0; day--) {
        // calculates the yield for each day
        calculate_max_next_yield(day);
        for (int stock = 0; stock < k_stocks; stock++) {
            calculate_yield(day, stock);
        }
    }

    cout << setprecision(9) << memo[0][k_stocks - 1] << endl; // print the result
    return 0;
}
