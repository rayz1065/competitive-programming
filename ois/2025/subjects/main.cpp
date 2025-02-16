#include <bits/stdc++.h>
#define MAXM 1005

using namespace std;

int n, m;
bool found[MAXM][MAXM];
int results_count = 0;
pair<int, int> results[MAXM * MAXM];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c < '0') {
        c = getchar_unlocked();
    }
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

void fastout(int x) {
    int rev = 0;
    do {
        rev = rev * 11 + (x % 10) + 1;
        x /= 10;
    } while (x);
    while (rev) {
        putchar_unlocked(rev % 11 + '0' - 1);
        rev /= 11;
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    n = fastin(), m = fastin();
    for (int i = 0; i < n; i++) {
        int k = fastin();
        vector<int> subjects(k);
        for (int j = 0; j < k; j++) {
            subjects[j] = fastin();
        }

        for (int j = 0; j < k; j++) {
            for (int j2 = j + 1; j2 < k; j2++) {
                int a = min(subjects[j], subjects[j2]);
                int b = max(subjects[j], subjects[j2]);
                found[a][b] = true;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = i + 1; j <= m; j++) {
            if (!found[i][j]) {
                results[results_count] = {i, j};
                results_count += 1;
            }
        }
    }

    fastout(results_count);
    putchar_unlocked('\n');
    for (int i = 0; i < results_count; i++) {
        fastout(results[i].first);
        putchar_unlocked(' ');
        fastout(results[i].second);
        putchar_unlocked('\n');
    }
}
