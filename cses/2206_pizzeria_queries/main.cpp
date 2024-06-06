#include <bits/stdc++.h>
#define MAXN 200005
#define ST_SIZE (1 << 19)
#define ST_LEFT(i) ((i) << 1)
#define ST_RIGHT(i) (((i) << 1) + 1)

using namespace std;

int n;
int prices[MAXN];
struct {
    int left_cost;
    int right_cost;
} segment_tree[ST_SIZE];

void st_set(int node, int l, int r, int target, int value) {
    if (!(l <= target && target <= r)) return;
    if (l == target && r == target) {
        segment_tree[node].left_cost = segment_tree[node].right_cost = value;
        return;
    }

    int mid = (l + r) >> 1;
    st_set(ST_LEFT(node), l, mid, target, value);
    st_set(ST_RIGHT(node), mid + 1, r, target, value);

    segment_tree[node].left_cost =
        min(segment_tree[ST_LEFT(node)].left_cost,
            segment_tree[ST_RIGHT(node)].left_cost + mid - l + 1);

    segment_tree[node].right_cost =
        min(segment_tree[ST_LEFT(node)].right_cost + r - (mid + 1) + 1,
            segment_tree[ST_RIGHT(node)].right_cost);
}

int st_get_cheapest(int node, int l, int r, int target) {
    if (r < target) return segment_tree[node].right_cost + abs(r - target);
    if (target < l) return segment_tree[node].left_cost + abs(l - target);
    if (l == r) return segment_tree[node].left_cost + abs(l - target);

    int mid = (l + r) >> 1;
    return min(st_get_cheapest(ST_LEFT(node), l, mid, target),
               st_get_cheapest(ST_RIGHT(node), mid + 1, r, target));
}

void set_price(int building, int price) {
    prices[building] = price;
    st_set(1, 0, n - 1, building, price);
}

int get_cheapest(int building) {
    return st_get_cheapest(1, 0, n - 1, building);
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> prices[i];
        set_price(i, prices[i]);
    }

    while (q--) {
        int query_type, building;
        cin >> query_type >> building;
        building--;

        if (query_type == 1) {
            int new_price;
            cin >> new_price;
            set_price(building, new_price);
        } else {
            cout << get_cheapest(building) << "\n";
        }
    }
}
