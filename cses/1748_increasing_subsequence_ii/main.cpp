#include <bits/stdc++.h>
#define MAXN 200005
#define MODV 1000000007
#define MOD(x) ((x) % MODV)

using namespace std;

int n, values[MAXN];
int fw[MAXN];

void fw_add(int i, int v) {
    for (i++; i < MAXN; i += i & (-i)) {
        fw[i] = MOD(fw[i] + v);
    }
}

int fw_sum(int i) {
    int res = 0;
    for (i++; i > 0; i -= i & (-i)) {
        res = MOD(res + fw[i]);
    }
    return res;
}

void compress_indexes() {
    vector<pair<int, int>> sorted(n);
    for (int i = 0; i < n; i++) {
        sorted[i] = {values[i], i};
    }
    sort(sorted.begin(), sorted.end());
    int curr = -1, unique_count = 0;
    for (int i = 0; i < n; i++) {
        if (sorted[i].first != curr) {
            curr = sorted[i].first;
            unique_count += 1;
        }
        values[sorted[i].second] = unique_count;
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    compress_indexes();

    fw_add(0, 1);
    for (int i = 0; i < n; i++) {
        int prev = fw_sum(values[i] - 1);
        fw_add(values[i], prev);
    }

    cout << MOD(fw_sum(n + 1) + MODV - 1) << "\n";
}
