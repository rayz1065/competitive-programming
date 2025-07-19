#include <bits/stdc++.h>

#include <algorithm>
#define ALF ('Z' - 'A' + 1)

using namespace std;

int freqs[ALF];

bool is_possible(char prev) {
    int total = 0;
    for (int i = 0; i < ALF; i++) {
        total += freqs[i];
    }
    int max_idx = max_element(freqs, freqs + ALF) - freqs;
    int prev_idx = prev - 'A';
    int max = freqs[max_idx];
    if (max_idx == prev_idx) {
        return max <= total / 2;
    }
    return max <= total / 2 + total % 2;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i++) {
        freqs[s[i] - 'A'] += 1;
    }

    if (!is_possible(0)) {
        cout << "-1\n";
        return 0;
    }

    string res;
    for (int i = 0; i < s.size(); i++) {
        bool found = false;
        for (int j = 0; j < ALF && !found; j++) {
            char nxt = j + 'A';
            if (freqs[j] == 0 || (!res.empty() && *res.rbegin() == nxt)) {
                continue;
            }
            freqs[j] -= 1;
            if (!is_possible(nxt)) {
                freqs[j] += 1;
                continue;
            }
            res.push_back(nxt);
            found = true;
        }
        assert(found);
    }

    cout << res << "\n";
}
