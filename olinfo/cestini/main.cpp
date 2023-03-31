#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int m_bins;
vector<int> bins[MAXN];

void inizia(int N, int M) {
    m_bins = M;
    for (int i = 0; i < N; i++) {
        bins[0].push_back(i);
    }
}

void sposta(int a, int b) {
    int x = bins[a][bins[a].size() - 1];
    bins[a].pop_back();
    bins[b].push_back(x);
}

int controlla(int a, int i) {
    if (bins[a].size() < i + 1) {
        return -1;
    }
    return bins[a][i];
}
