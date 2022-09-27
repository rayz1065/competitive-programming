#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

#define MAXN 10000005

void fastin (int &v) {
    v = 0;
    char c = getchar_unlocked();
    for (; c >= '0'; c = getchar_unlocked()) {
        v = v * 10 + c - '0';
    }
}

// input data
int n;
int heights[MAXN];
int sorted_heights[MAXN];

// ufds
bool marked[MAXN];
typedef struct GroupInfo {
    int highest_left;
    int highest_right;
    int left_border;
    int right_border;
} GroupInfo;

int ufds_parent[MAXN];
GroupInfo* ufds_info[MAXN];

int info_storage_nxt = 0; // next available place in the storage
GroupInfo info_storage[MAXN/3 + 5];

GroupInfo* allocate_storage () {
    // allocate some new space...
    return info_storage + info_storage_nxt++;
}

GroupInfo get_group_info (int i) {
    if (ufds_info[i] != nullptr) {
        return *ufds_info[i];
    }
    return { i, i, i, i };
}

// optimizations
char ufds_rank[MAXN];

int ufds_group (int i) {
    if (ufds_parent[i] == i) {
        return i;
    }
    return ufds_parent[i] = ufds_group(ufds_parent[i]);
}

void ufds_join (int i, int j) {
    i = ufds_group(i), j = ufds_group(j);

    GroupInfo gi_i = get_group_info(i);
    GroupInfo gi_j = get_group_info(j);

    // recalculate the leftmost and rightmost highest points
    int i_height = heights[gi_i.highest_left];
    int j_height = heights[gi_j.highest_left];
    int new_hi_left, new_hi_right;
    if (i_height == j_height) {
        new_hi_left = min(gi_i.highest_left, gi_j.highest_left);
        new_hi_right = max(gi_i.highest_right, gi_j.highest_right);
    } else if (i_height > j_height) {
        new_hi_left = gi_i.highest_left;
        new_hi_right = gi_i.highest_right;
    } else {
        new_hi_left = gi_j.highest_left;
        new_hi_right = gi_j.highest_right;
    }

    // recompute left and right borders
    int new_left_border = min(gi_i.left_border, gi_j.left_border);
    int new_right_border = max(gi_i.right_border, gi_j.right_border);

    // recalculate the group parents and rank
    if (ufds_rank[i] > ufds_rank[j]) {
        ufds_parent[j] = i;
    } else if (ufds_rank[j] > ufds_rank[i]) {
        ufds_parent[i] = j;
    } else {
        ufds_parent[i] = j;
        ufds_rank[j]++;
    }

    // assign information
    GroupInfo *new_info = nullptr;
    if (ufds_info[i] != nullptr) {
        new_info = ufds_info[i];
    }
    if (ufds_info[j] != nullptr) {
        // note, this should clear out the excess memory but should not be necessary
        // if (new_info != nullptr) {}
        new_info = ufds_info[j];
    }
    if (new_info == nullptr) {
        new_info = allocate_storage();
    }
    i = ufds_parent[i];

    new_info->highest_left = new_hi_left;
    new_info->highest_right = new_hi_right;
    new_info->left_border = new_left_border;
    new_info->right_border = new_right_border;
    ufds_info[i] = new_info;
}

void ufds_init () {
    for (int i = 0; i < n; i++) {
        ufds_parent[i] = i;
    }
    // fill (ufds_rank, ufds_rank + n, 0);
    fill (marked, marked + n, 0);
}

void mark (int i) {
    // set i to marked and join with nearest marked
    marked[i] = true;
    if (i + 1 < n && marked[i + 1]) {
        ufds_join(i, i + 1);
    }
    if (i - 1 >= 0 && marked[i - 1]) {
        ufds_join(i, i - 1);
    }
}

int compute_table (int i) {
    i = ufds_group(i);
    GroupInfo gi_i = get_group_info(i);

    if (gi_i.highest_left == gi_i.highest_right) {
        // unstable
        return 0;
    }
    int l0 = gi_i.highest_right - gi_i.highest_left + 1;
    int capacity = max(l0 - 2, 0);
    int sl = gi_i.highest_left - gi_i.left_border;
    int sr = gi_i.right_border - gi_i.highest_right;
    int off_balance = max(sl, sr) - min(sl, sr);
    // printf("table @ %d, l0 = %d, cap = %d, sl = %d, sr = %d, off = %d", i, l0, capacity, sl, sr, off_balance);

    return l0 + min(sl, sr) * 2 + min(capacity, off_balance);
}

bool compare_heights (int i, int j) {
    return heights[i] < heights[j];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fastin(n);
    for (int i = 0; i < n; i++) {
        fastin(heights[i]);
    }

    ufds_init();

    // order the heights
    for (int i = 0; i < n; i++) {
        sorted_heights[i] = i;
    }
    sort(sorted_heights, sorted_heights + n, compare_heights);

    // add the heights in order
    int best_sol = 0;
    for (int i = 0; i < n; i++) {
        int curr_height = heights[sorted_heights[i]];
        int j;
        for (j = i; j < n && heights[sorted_heights[j]] == curr_height; j++) {
            // mark all the new points
            mark(sorted_heights[j]);
        }
        for (j = i; j < n && heights[sorted_heights[j]] == curr_height; j++) {
            // find the longest contiguos table that can be placed
            best_sol = max(best_sol, compute_table(sorted_heights[j]));
        }
        i = j - 1;
    }

    // insert your code here

    cout << best_sol << endl; // print the result
    return 0;
}
