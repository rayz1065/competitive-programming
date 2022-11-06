#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n = 15;
ll new_coins[15];
int values[15] = { 1, 2, 5, 10, 20, 50,
                   100, 200, 500, 1000, 2000, 5000,
                   10000, 20000, 50000 };

int main () {
    ll tot_money = 0;
    for (int i = 0; i < n; i++) {
        ll am;
        cin >> am;
        tot_money += am * values[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        ll am = tot_money / values[i];
        new_coins[i] = am;
        tot_money -= am * values[i];
    }
    for (int i = 0; i < n; i++) {
        cout << new_coins[i] << " \n"[i + 1 == n];
    }
}
