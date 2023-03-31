#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXM 1000005

using namespace std;

FILE *fin, *fout;
int m_count, f_count, n_couples;
vector<int> graph[MAXM];
int best_for_f[MAXM];

int fastin() {
    int v = 0;
    char c = fgetc(fin);
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = fgetc(fin);
    }
    return v;
}

int main () {
#ifdef DEBUG
    fin = stdin;
    fout = stdout;
#else
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
#endif
    m_count = fastin();
    f_count = fastin();
    n_couples = fastin();
    for (int i = 0; i < n_couples; i++) {
        int a, b;
        a = fastin() - 1;
        b = fastin() - 1;
        graph[a].push_back(b);
    }
    for (int i = 0; i < m_count; i++) {
        sort(graph[i].begin(), graph[i].end());
    }

    set<int> stored_fs;
    stored_fs.insert(f_count);
    best_for_f[f_count] = 0;
    for (int m = m_count - 1; m >= 0; m--) {
        for (auto f: graph[m]) {
            auto x = stored_fs.lower_bound(f + 1);
            int new_val = best_for_f[*x] + 2;
            if (x != stored_fs.begin()) {
                // cout << "Removing " << (*x) << " that had val " << best_for_f[*x] << "\n";
                x--;
                stored_fs.erase(x);
            }
            // cout << "Adding " << f << ", assigning " << (new_val) << "\n";
            stored_fs.insert(f);
            best_for_f[f] = new_val;
            // for (int i = 0; i <= f_count + 1; i++) {
            //     if (stored_fs.find(i) == stored_fs.end()) {
            //         cout << "-";
            //     } else {
            //         cout << best_for_f[i];
            //     }
            //     cout << " \n"[i == f_count - 1];
            // }
        }
    }
    auto sol = stored_fs.lower_bound(0);
    fprintf(fout, "%d\n", best_for_f[*sol]);
}