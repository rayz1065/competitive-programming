#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 100005

using namespace std;

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int n;
int distances[MAXN];
struct DistInfo {
    int i;
    int min;
    int max;
};

int solve () {
    int s = 0;
    vector<DistInfo> dist_stack;
    for (int i = 0; i < n; i++) {
        while (dist_stack.size() > 0 && dist_stack.rbegin()->min > distances[i]) {
            dist_stack.pop_back();
        }
        while (dist_stack.size() > 1 && dist_stack[dist_stack.size() - 2].max <= distances[i]) {
            dist_stack.pop_back();
        }
        if (dist_stack.size() == 0 || distances[i] < dist_stack.rbegin()->max) {
            dist_stack.push_back({ i, distances[i], distances[i] });
        }
        if (distances[i] >= dist_stack.rbegin()->max) {
            dist_stack.rbegin()->max = distances[i];
            s = max(s, i - dist_stack.rbegin()->i + 1);
        }
    }
    return s;
}

int main () {
#ifndef DEBUG
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
#endif
    n = fastin();
    for (int i = 0; i < n; i++) {
        distances[i] = fastin();
    }

    cout << solve() << "\n";
}
