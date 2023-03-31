#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n_houses;
vector<int> heights;
vector<int> jump_left;
vector<int> jump_right;

#define FW_LEFT(x) (x << 1)
#define FW_RIGHT(x) ((x << 1) + 1)
int fenwick[MAXN * 4];

void _fw_store (int node, int left_bound, int right_bound, int target, int val) {
    if (left_bound > target || right_bound < target) {
        return ;
    }
    if (left_bound == right_bound) {
        fenwick[node] = val;
        return ;
    }

    int mid = (left_bound + right_bound) / 2;
    _fw_store(FW_LEFT(node), left_bound, mid, target, val);
    _fw_store(FW_RIGHT(node), mid + 1, right_bound, target, val);
    fenwick[node] = min(fenwick[FW_LEFT(node)], fenwick[FW_RIGHT(node)]);
}

void fw_store (int target, int val) {
    _fw_store(1, 0, n_houses, target, val);
}

int _fw_min_range (int node, int left_bound, int right_bound, int target_left, int target_right) {
    if (left_bound > target_right || right_bound < target_left) {
        // completely outside of range...
        return INT_MAX >> 1;
    }
    if (target_left <= left_bound && right_bound <= target_right) {
        // completely within the target
        return fenwick[node];
    }
    int mid = (left_bound + right_bound) / 2;
    return min(
        _fw_min_range(FW_LEFT(node), left_bound, mid, target_left, target_right),
        _fw_min_range(FW_RIGHT(node), mid + 1, right_bound, target_left, target_right)
    );
}

int fw_min_range (int left, int right) {
    return _fw_min_range(1, 0, n_houses, left, right);
}

int salta (int n_houses, vector<int> heights, vector<int> jump_left, vector<int> jump_right){
    ::n_houses = n_houses;
    ::heights = heights;
    ::jump_left = jump_left;
    ::jump_right = jump_right;

    fill(fenwick, fenwick + 4 * MAXN, INT_MAX >> 1);

    fw_store(n_houses, 0);
    for (int i = n_houses - 1; i >= 0; i--) {
        // find the best house to jump on
        int left = jump_left[i] + i, right = jump_right[i] + i;
        int best = fw_min_range(left, right);
        int actual = max(best, heights[i]);
        fw_store(i, actual);
        // cout << i << " ranges " << left << "," << right << " best is " << best << " with h " << heights[i] << " is " << actual << "\n";
    }

    return fw_min_range(0, 0);
}