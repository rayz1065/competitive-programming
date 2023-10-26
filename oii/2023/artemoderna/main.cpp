#include <bits/stdc++.h>

using namespace std;

bool ordina(int n, vector<int> items, vector<int> &splits) {
    items.push_back(INT_MAX >> 1); // dummy item

    int first_idx = 0;
    for (int i = 0; i < n; i++) {
        if (items[i] < items[i + 1]) {
            splits.push_back(i - first_idx + 1);
            first_idx = i + 1;
        }
    }

    // apply the sort
    first_idx = 0;
    for (auto split_size: splits) {
        reverse(items.begin() + first_idx, items.begin() + first_idx + split_size);
        first_idx += split_size;
    }

    for (int i = 0; i < n; i++) {
        if (items[i] > items[i + 1]) {
            // sorted incorrectly
            return false;
        }
    }

    return true;
}
