#include <bits/stdc++.h>

using namespace std;

int n, m;

long long solve (int i, int last_digit, long long curr_mod) {
    if (i == n) {
        return curr_mod;
    }
    long long s = curr_mod;
    for (int j = 3; j < 10; j += 3) {
        if (j != last_digit) {
            s = max(s, solve(i + 1, j, (curr_mod * 10 + j) % m));
        }
    }
    return s;
}

long long occulta(int n, int m) {
    ::n = n;
    ::m = m;
    return solve(0, 0, 0);
}


int main() {
    FILE *fr, *fw;
    int T, N, M, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(1 == fscanf(fr, "%d", &T));
    for (i=0; i<T; i++) {
        assert(2 == fscanf(fr, "%d %d", &N, &M));
        fprintf(fw, "%d ", occulta(N, M));
    }

    fprintf(fw, "\n");
    fclose(fr);
    fclose(fw);
    return 0;
}