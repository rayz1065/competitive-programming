#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n;
int depth[MAXN];
vector<pair<int, int>> children[MAXN];

int get_dist(char rel) {
    if (rel == 'B') return 3;
    if (rel == 'N') return 2;
    return 1;
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#else
    cin.tie(NULL);
    cout.tie(NULL);
#endif
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i < n; i++) {
        char c;
        int parent;
        cin >> c >> parent;
        children[parent].push_back({i, get_dist(c)});
    }

    queue<int> ff;
    ff.push(0);

    while (!ff.empty()) {
        int node = ff.front();
        ff.pop();
        for (auto j : children[node]) {
            depth[j.first] = depth[node] + j.second;
            ff.push(j.first);
        }
    }

    cout << *max_element(depth, depth + n) << "\n";
}
