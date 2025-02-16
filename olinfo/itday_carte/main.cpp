#include <bits/stdc++.h>

using namespace std;

int gioca(int n, int k, vector<vector<int>> decks) {
    int res = 0;
    int last_picked = -1;

    set<pair<int, int>> ff;
    vector<int> deck_indexes(decks.size(), 0);
    for (int i = 0; i < decks.size(); i++) {
        ff.insert({decks[i][0], i});
    }

    while (!ff.empty()) {
        auto curr = ff.begin();
        int deck_idx = curr->second;
        int card = curr->first;
        ff.erase(curr);

        if (card > last_picked) {
            last_picked = card;
            res += 1;
        }

        deck_indexes[deck_idx] += 1;
        int next_index = deck_indexes[deck_idx];

        if (next_index < decks[deck_idx].size()) {
            ff.insert({decks[deck_idx][next_index], deck_idx});
        }
    }

    return res;
}
