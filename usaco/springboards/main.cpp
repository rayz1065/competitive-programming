#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int grid_size, n;
// y1 -> { x1, x2, y2 }
struct Springboard {
    int x1, y1, x2, y2;

    bool operator<(const Springboard &other) const {
        return this->y1 < other.y1;
    }
} springboards[MAXN];
// y -> { x, distance_sprung }
set<pair<int, pair<int, int>>> landing;
// x -> distance_sprung
set<pair<int, int>> min_distances;

void add_distance(int x, int distance_sprung) {
    auto nxt = min_distances.upper_bound({x, -1});
    nxt--;

    // check that the previous isn't already better
    if (nxt->second >= distance_sprung) {
        return;
    }

    // remove worst values with greater x
    while (true) {
        auto curr = nxt;
        curr++;
        if (distance_sprung < curr->second) {
            break;
        }
        // can move from x to curr->first
        min_distances.erase(curr);
    }

    min_distances.insert({x, distance_sprung});
}

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("boards.in", ios::in);
    cout.open("boards.out", ios::out);
#endif
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> grid_size >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        springboards[i] = {x1, y1, x2, y2};
    }

    sort(springboards, springboards + n);

    vector<pair<pair<int, int>, pair<int, bool>>> locations;
    locations.reserve(2 * n + 5);
    for (int i = 0; i < n; i++) {
        locations.push_back(
            {{springboards[i].y1, springboards[i].x1}, {i, false}});
        locations.push_back(
            {{springboards[i].y2, springboards[i].x2}, {i, true}});
    }
    sort(locations.begin(), locations.end());

    min_distances.insert({-1, 0});  // dummy
    min_distances.insert({0, 0});
    min_distances.insert({grid_size + 1, INT_MAX});  // dummy

    // NOTE: need to consider springs where y1 == y2
    for (auto location : locations) {
        auto yx = location.first;
        auto i_end = location.second;
        int x = yx.second, y = yx.first, spring_idx = i_end.first;
        bool is_end = i_end.second;

        if (is_end) {
            // update min_distances
            auto x_distance = landing.begin()->second;
            assert(x_distance.first == x);
            add_distance(x_distance.first, x_distance.second);
            landing.erase(landing.begin());
        } else {
            auto spring = springboards[spring_idx];
            auto nxt = min_distances.upper_bound({spring.x1, INT_MAX});
            nxt--;
            int distance =
                nxt->second + (spring.x2 - spring.x1) + (spring.y2 - spring.y1);
            landing.insert({spring.y2, {spring.x2, distance}});
        }
    }

    auto nxt = min_distances.rbegin();
    nxt++;
    cout << 2 * grid_size - nxt->second << "\n";
}
