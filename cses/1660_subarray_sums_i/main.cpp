#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n, values[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int target;
    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    int sum = 0, res = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < i && sum + values[i] > target) {
            sum -= values[j++];
        }
        sum += values[i];
        res += sum == target;
    }

    cout << res << "\n";
}
