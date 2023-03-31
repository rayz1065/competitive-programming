#include <bits/stdc++.h>
using namespace std;

long long aggiorna(int N, vector<int> A, vector<int> B) {
    long long s = 0;
    for (int i = N - 2; i >= 0; i--) {
        // find the max for this one...
        int max_updates =(A[i + 1] - A[i]) / B[i];
        s += max_updates;
        A[i] += max_updates * B[i];
    }
    return s;
}
