#include <bits/stdc++.h>

using namespace std;

int traffico(int N, vector<int> S) {
    int curr = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] % 2 != i % 2) {
            curr += 1;
        }
    }
    int best = curr;
    curr = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] % 2 == i % 2) {
            curr += 1;
        }
    }
    return min(best, curr);
}
