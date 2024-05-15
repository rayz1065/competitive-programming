#include <bits/stdc++.h>
#define MAXN 300005

using namespace std;

typedef long long ll;

int n;
int names[MAXN];
pair<int, int> graph[MAXN];

tuple<ll, int, vector<pair<int, int>> *> solve(int node) {
    int len = names[node] + 2;
    int left = -len + len / 2 + 1;
    int right = len / 2;

    ll res = len * 3;

    if (graph[node].first == -1) {
        // leaf node

        vector<pair<int, int>> *positions = new vector<pair<int, int>>();
        positions->push_back({left, right});
        return {res, 0, positions};
    }

    if (graph[node].second == -1) {
        /**
         * | no branching
         * +
         * |
         */

        ll sub_cost;
        int center;
        vector<pair<int, int>> *positions;
        tie(sub_cost, center, positions) = solve(graph[node].first);

        // recenter the node
        left += center, right += center;
        res += sub_cost + 3;
        positions->push_back({left, right});

        return {res, center, positions};
    }

    /**
     *  |  branching
     * -+-
     * | |
     */

    ll sub_cost_l, sub_cost_r;
    int center_l, center_r;
    vector<pair<int, int>> *positions;
    vector<pair<int, int>> *positions_2;

    tie(sub_cost_l, center_l, positions) = solve(graph[node].first);
    tie(sub_cost_r, center_r, positions_2) = solve(graph[node].second);

    // compute an offset to move the (smallest) child by
    int minimum_offset = INT_MIN >> 1;
    for (int i = 0; i < (int)positions->size() && i < (int)positions_2->size();
         i++) {
        auto l = (*positions)[(int)positions->size() - i - 1];
        auto r = (*positions_2)[(int)positions_2->size() - i - 1];
        minimum_offset = max(minimum_offset, l.second - r.first + 1);
    }

    // ensure proper centering
    if ((center_r - (center_l - minimum_offset) + 1) % 2 != 1) {
        minimum_offset += 1;
    }

    // offset the smallest child, make `positions` the longest child
    if (positions->size() < positions_2->size()) {
        center_l -= minimum_offset;
        for (int i = 0; i < (int)positions->size(); i++) {
            (*positions)[i].first -= minimum_offset;
            (*positions)[i].second -= minimum_offset;
        }
        swap(positions, positions_2);
    } else {
        for (int i = 0; i < (int)positions_2->size(); i++) {
            (*positions_2)[i].first += minimum_offset;
            (*positions_2)[i].second += minimum_offset;
        }
        center_r += minimum_offset;
    }

    // combine the two, small to large
    for (int i = 0; i < (int)positions_2->size(); i++) {
        int j = (int)positions->size() - (int)positions_2->size() + i;
        auto l = (*positions)[j], r = (*positions_2)[i];
        (*positions)[j] = {min(l.first, r.first), max(l.second, r.second)};
    }

    // recenter the node
    int center = (center_l + center_r) / 2;
    left += center, right += center;
    positions->push_back({left, right});
    res += sub_cost_l + sub_cost_r + 3 + center_r - center_l + 1;

    delete positions_2;

    return {res, center, positions};
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n; i++) {
        graph[i] = {-1, -1};
    }

    string name;
    cin >> name;
    names[0] = name.size();

    for (int i = 1; i < n; i++) {
        int parent;
        cin >> name >> parent;
        parent--;
        names[i] = name.length();
        if (graph[parent].first == -1) {
            graph[parent].first = i;
        } else {
            graph[parent].second = i;
        }
    }

    ll res;
    int center;
    vector<pair<int, int>> *positions;
    tie(res, center, positions) = solve(0);

    cout << res << "\n";
}
