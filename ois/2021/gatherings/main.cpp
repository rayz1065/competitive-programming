#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int distances[MAXN];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, d;
    cin >> n >> d;

    for (int i = 0; i < n; i++) {
        cin >> distances[i];
    }
    long long s = 0;
    for (int i = 0; i < n; i++) {
        int next = lower_bound(distances, distances + n, distances[i] + d) - distances;
        s += next - i - 1;
    }
    cout << s << "\n";
}
