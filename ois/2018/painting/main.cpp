#include <bits/stdc++.h>
#define MAXN 15
#define MAXK 15

using namespace std;

int n;
char painting[MAXN][MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> painting[i];
    }

    vector<int> i(k + 1, 0);
    while (i[k] == 0) {
        vector<int> j(k + 1, 0);
        int asterisks = 0;

        for (int k_ = 0; k_ < k; k_++) {
            asterisks += painting[i[k_]][j[k_]] == '*';
        }

        while (j[k] == 0) {
            putchar_unlocked(asterisks == 0 ? '.' : '*');

            for (int k_ = 0; k_ <= k; k_++) {
                asterisks -= painting[i[k_]][j[k_]] == '*';
                j[k_] = (j[k_] + 1) % n;
                asterisks += painting[i[k_]][j[k_]] == '*';
                if (j[k_] > 0) {
                    break;
                }
            }
        }
        putchar_unlocked('\n');

        for (int k_ = 0; k_ <= k; k_++) {
            asterisks -= painting[i[k_]][j[k_]] == '*';
            i[k_] = (i[k_] + 1) % n;
            asterisks += painting[i[k_]][i[k_]] == '*';
            if (i[k_] > 0) {
                break;
            }
        }
    }
}
