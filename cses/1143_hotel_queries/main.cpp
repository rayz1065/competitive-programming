#include <bits/stdc++.h>
#define MAXN 200005
#define ST_SIZE (1 << 19)
#define ST_LEFT(i) ((i) << 1)
#define ST_RIGHT(i) (((i) << 1) + 1)

using namespace std;

int n;
int hotels[MAXN];

struct {
    int max;
} segment_tree[ST_SIZE];

void st_set(int node, int l, int r, int target, int value) {
    if (!(l <= target && target <= r)) return;
    if (l == r) {
        segment_tree[node].max = value;
        return;
    }

    int mid = (l + r) >> 1;
    st_set(ST_LEFT(node), l, mid, target, value);
    st_set(ST_RIGHT(node), mid + 1, r, target, value);

    segment_tree[node].max =
        max(segment_tree[ST_LEFT(node)].max, segment_tree[ST_RIGHT(node)].max);
}

int st_find_hotel(int node, int l, int r, int value) {
    if (segment_tree[node].max < value) return -1;
    if (l == r) return l;

    int mid = (l + r) >> 1;
    int l_res = st_find_hotel(ST_LEFT(node), l, mid, value);
    if (l_res != -1) return l_res;
    return st_find_hotel(ST_RIGHT(node), mid + 1, r, value);
}

void st_init() {
    for (int i = 0; i < n; i++) {
        st_set(1, 0, n - 1, i, hotels[i]);
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> hotels[i];
    }

    st_init();

    while (q--) {
        int tourists;
        cin >> tourists;

        int index = st_find_hotel(1, 0, n - 1, tourists);
        if (index != -1) {
            hotels[index] -= tourists;
            st_set(1, 0, n - 1, index, hotels[index]);
        }

        cout << index + 1 << " \n"[q == 0];
    }
}
