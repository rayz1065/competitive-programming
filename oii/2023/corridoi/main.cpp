#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
vector<pair<int, int>> graph[MAXN];
ll all_distances[3][MAXN];

void dijkstra(int node, ll *dist) {
    set<pair<ll, int>> ff;
    fill(dist, dist + MAXN, LLONG_MAX >> 1);
    dist[node] = 0ll;
    ff.insert({dist[node], node});

    while (!ff.empty()) {
        node = ff.begin()->second;
        ll curr_dist = ff.begin()->first;
        ff.erase(ff.begin());

        if (curr_dist > dist[node]) {
            continue ;
        }

        for (auto branch: graph[node]) {
            ll new_dist = curr_dist + branch.second;
            if (new_dist < dist[branch.first]) {
                dist[branch.first] = new_dist;
                ff.insert({dist[branch.first], branch.first});
            }
        }
    }
}

void dijkstra_heap(int node, ll *dist) {
    vector<pair<ll, int>> ff;
    fill(dist, dist + MAXN, LLONG_MAX >> 1);
    dist[node] = 0ll;
    ff.push_back({ -dist[node], node });

    while (!ff.empty()) {
        node = ff.begin()->second;
        ll curr_dist = -ff.begin()->first;
        pop_heap(ff.begin(), ff.end());
        ff.pop_back();

        if (curr_dist > dist[node]) {
            continue ;
        }

        for (auto branch: graph[node]) {
            ll new_dist = curr_dist + branch.second;
            if (new_dist < dist[branch.first]) {
                dist[branch.first] = new_dist;
                ff.push_back({ -dist[branch.first], branch.first });
                push_heap(ff.begin(), ff.end());
            }
        }
    }
}

pair<ll, ll> subtract_min(ll from, ll amount) {
    ll subtracted = min(from, amount);
    return { from - subtracted, amount - subtracted };
}

ll compute_cost(ll a, ll b, ll cart) {
    tie(a, cart) = subtract_min(a, cart);
    tie(b, cart) = subtract_min(b, cart);

    return a * 2 + b;
}

pair<ll, ll> best_at(ll cart) {
    pair<ll, ll> best;
    ll best_cost = LLONG_MAX >> 1;

    for (int i = 0; i < n; i++) {
        ll a = all_distances[1][i];
        ll b = all_distances[0][i] + all_distances[2][i];
        
        ll curr_cost = compute_cost(a, b, cart);
        if (curr_cost < best_cost) {
            best_cost = curr_cost;
            best = { a, b };
        }
    }

    return best;
}

vector<ll> simple_solve(vector<ll> carts) {
    vector<ll> solution;

    for (auto cart: carts) {
        auto best = best_at(cart);
        // cerr << "For " << cart << " best is " << best.first << " " << best.second << "\n";
        solution.push_back(compute_cost(best.first, best.second, cart));
    }

    return solution;
}

ll find_intersection(pair<ll, ll> prev, pair<ll, ll> candidate) {
    // binary search for the first point where candidate is better
    // this can probably be done in constant time instead
    ll left_end = 0;
    ll right_end = candidate.first + 1;
    ll found = -1;

    while (left_end <= right_end) {
        ll mid = (left_end + right_end) >> 1;

        ll prev_cost = compute_cost(prev.first, prev.second, mid);
        ll curr_cost = compute_cost(candidate.first, candidate.second, mid);

        if (curr_cost < prev_cost) {
            // this is better
            found = mid;
            right_end = mid - 1;
        } else {
            // try further right
            left_end = mid + 1;
        }
    }

    return found;
}

bool comparator(pair<ll, pair<ll, ll>> a, pair<ll, pair<ll, ll>> b) {
    return a.first < b.first;
}

bool comparator_2(pair<ll, ll> a, pair<ll, ll> b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

vector<ll> solve(vector<ll> carts) {
    // precompute all solutions
    vector<pair<ll, ll>> candidate_locations; // a, b
    for (int i = 0; i < n; i++) {
        ll a = all_distances[1][i];
        ll b = all_distances[0][i] + all_distances[2][i];

        candidate_locations.push_back({ a, b });
    }

    sort(candidate_locations.begin(), candidate_locations.end(), comparator_2);

    // contains all the most efficient points to switch at
    vector<pair<ll, pair<ll, ll>>> switch_points;

    switch_points.push_back({ 0, best_at(0) });
    for (auto candidate: candidate_locations) {
        auto prev = switch_points.rbegin()->second;

        ll intersection = find_intersection(prev, candidate);
        if (intersection == -1) {
            // candidate is worse everywhere
            continue ;
        }

        while (intersection < switch_points.rbegin()->first) {
            switch_points.pop_back();
            prev = switch_points.rbegin()->second;
            intersection = find_intersection(prev, candidate);
        }

        switch_points.push_back({ intersection, candidate });
    }

    vector<ll> solution;
    for (auto cart: carts) {
        pair<ll, pair<ll, ll>> ugly = { cart, { 1ll,2ll } }; // hack to use upper_bound
        auto switch_point = upper_bound(switch_points.begin(), switch_points.end(), ugly, comparator);
        switch_point--;
        auto curr = switch_point->second;
        solution.push_back(compute_cost(curr.first, curr.second, cart));
    }

    return solution;
}

vector<ll> shorten(int n, int m_branches, int q_queries, vector<ll> carts,
                   vector<int> corridor_a, vector<int> corridor_b,
                   vector<int> corridor_paintings) {
    ::n = n;

    for (int i = 0; i < m_branches; i++) {
        graph[corridor_a[i]].push_back({ corridor_b[i], corridor_paintings[i] });
        graph[corridor_b[i]].push_back({ corridor_a[i], corridor_paintings[i] });
    }


    for (int i = 0; i < 3; i++) {
        dijkstra_heap(i, all_distances[i]);
    }

#ifdef SIMPLE
    return simple_solve(carts);
#endif
    return solve(carts);
}
