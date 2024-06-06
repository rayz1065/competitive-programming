#include <bits/stdc++.h>
#define MAXN 200005
#define ST_SIZE (1 << 19)
#define ST_LEFT(i) ((i) << 1)
#define ST_RIGHT(i) (((i) << 1) + 1)
using namespace std;

int n;
string bits;

struct {
    bool right_bit;
    int right_length;
    bool left_bit;
    int left_length;
    int best;
} segment_tree[ST_SIZE];

void st_set(int node, int l, int r, int target, bool value) {
    if (!(l <= target && target <= r)) return;
    if (l == r) {
        segment_tree[node] = {value, 1, value, 1, 1};
        return;
    }

    int mid = (l + r) >> 1;
    st_set(ST_LEFT(node), l, mid, target, value);
    st_set(ST_RIGHT(node), mid + 1, r, target, value);

    segment_tree[node] = {segment_tree[ST_RIGHT(node)].right_bit,
                          segment_tree[ST_RIGHT(node)].right_length,
                          segment_tree[ST_LEFT(node)].left_bit,
                          segment_tree[ST_LEFT(node)].left_length,
                          max(segment_tree[ST_LEFT(node)].best,
                              segment_tree[ST_RIGHT(node)].best)};

    if (segment_tree[ST_RIGHT(node)].right_length == r - (mid + 1) + 1 &&
        segment_tree[ST_RIGHT(node)].right_bit ==
            segment_tree[ST_LEFT(node)].right_bit) {
        // right is all the same
        segment_tree[node].right_length +=
            segment_tree[ST_LEFT(node)].right_length;
    }

    if (segment_tree[ST_LEFT(node)].left_length == mid - l + 1 &&
        segment_tree[ST_LEFT(node)].left_bit ==
            segment_tree[ST_RIGHT(node)].left_bit) {
        // left is all the same
        segment_tree[node].left_length +=
            segment_tree[ST_RIGHT(node)].left_length;
    }

    if (segment_tree[ST_LEFT(node)].right_bit ==
        segment_tree[ST_RIGHT(node)].left_bit) {
        // note: any of the two above cases imply this one
        segment_tree[node].best =
            max(segment_tree[node].best,
                segment_tree[ST_LEFT(node)].right_length +
                    segment_tree[ST_RIGHT(node)].left_length);
    }
}

void set_bit(int index, bool value) {
    bits[index] = value ? '1' : '0';
    st_set(1, 0, n - 1, index, value);
}

int count_longest_identical() { return segment_tree[1].best; }

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> bits;
    n = bits.length();
    for (int i = 0; i < n; i++) {
        set_bit(i, bits[i] == '1');
    }

    int q;
    cin >> q;

    while (q--) {
        int bit_index;
        cin >> bit_index;
        bit_index--;

        set_bit(bit_index, bits[bit_index] == '0');
        cout << count_longest_identical() << " \n"[q == 0];
    }
}
