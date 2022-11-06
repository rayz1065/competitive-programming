#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXL 10005
#define INF (LLONG_MAX >> 2)
#define MAXK (26 * 26 * 26 + 5)
#define TWOL (26 * 26)

using namespace std;

typedef long long ll;

ll n;
int l, k;
bool words[MAXK];
ll memo[MAXL][TWOL + 5];

int word_to_int (string word) {
    int s = 0;
    for (int i = 0; i < word.length(); i++) {
        s = (s * 26 + word[i] - 'a');
    }
    return s;
}

inline int last_two_letters (int i) {
    return i % TWOL;
}

ll count_words (int i, int twol) {
    if (i == l) return 1;
    if (memo[i][twol] != -1) return memo[i][twol];
    memo[i][twol] = 0;
    for (int next_l = 0; next_l < 26; next_l++) {
        if (i < 2 || words[twol * 26 + next_l]) {
            // valid word
            memo[i][twol] += count_words(i + 1, last_two_letters(twol * 26 + next_l));
            if (memo[i][twol] >= INF) return memo[i][twol] = INF;
        }
    }
    return memo[i][twol];
}

void find_word (int i, int twol, ll skipped, string &sol) {
    if (i == l) return ;
    for (int next_l = 0; next_l < 26; next_l++) {
        if (i < 2 || words[twol * 26 + next_l]) {
            ll curr = count_words(i + 1, last_two_letters(twol * 26 + next_l));
            skipped += curr;
            if (skipped >= n) {
                // found the next letter
                sol += next_l + 'a';
                skipped -= curr;
                find_word(i + 1, last_two_letters(twol * 26 + next_l), skipped, sol);
                return ;
            }
        }
    }
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> l >> k;
    for (int i = 0; i < k; i++) {
        string word;
        cin >> word;
        words[word_to_int(word)] = true;
    }
    for (int i = 0; i < l; i++) {
        fill(memo[i], memo[i] + TWOL, -1);
    }

    string sol;
    find_word(0, 0, 0, sol);
    cout << sol << "\n";
}
