#include <bits/stdc++.h>

using namespace std;

// input data
int n_days, k_stocks;
vector< vector<int> > buy_on_day, sell_on_day;

double profit (int day, int owned_stock, double quantity_owned) {
    if (day == n_days - 1) {
        return quantity_owned * sell_on_day[day][owned_stock];
    }
    // sell everything and buy nothing else
    double money = quantity_owned * sell_on_day[day][owned_stock];
     // don't sell yet
    double max_profit = max(money, profit(day + 1, owned_stock, quantity_owned));

    // sell and buy something else
    for (int j = 0; j < k_stocks; j++) {
        max_profit = max(max_profit, profit(day + 1, j, money / buy_on_day[day][j]));
    }

    return max_profit;
}

int main() {
	ios::sync_with_stdio(false);

    cin >> n_days >> k_stocks;

    k_stocks+= 1;
    buy_on_day.resize(n_days, vector<int>(k_stocks));
    sell_on_day.resize(n_days, vector<int>(k_stocks));
    for (int i=0; i<n_days; i++) {
        for (int j=0; j<k_stocks - 1; j++) {
            cin >> buy_on_day[i][j] >> sell_on_day[i][j];
        }
        buy_on_day[i][k_stocks - 1] = 1;
        sell_on_day[i][k_stocks - 1] = 1;
    }

    // insert your code here

    cout << setprecision(9) << profit(0, k_stocks - 1, 1.0) << endl; // print the result
    return 0;
}
