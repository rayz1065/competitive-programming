#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int frequencies[MAXN];
int order[MAXN];

bool frequency_order(int i, int j) { return frequencies[i] > frequencies[j]; }

vector<int> bilancia(int n, int m, vector<vector<int>> S) {
    for (auto &tester : S) {
        for (auto problem : tester) {
            frequencies[problem] += 1;
        }
    }
    for (int i = 0; i < m; i++) {
        order[i] = i;
    }
    sort(order, order + m, frequency_order);
    for (int i = 0; i < n; i++) {
        unordered_set<int> tester;
        for (auto j : S[i]) {
            tester.insert(j);
        }
        for (int j = 0; j < tester.size(); j++) {
            if (tester.find(order[j]) == tester.end()) {
                return {};
            }
        }
    }
    vector<int> res;
    for (int i = 0; i < m; i++) {
        res.push_back(order[i]);
    }
    return res;
}
