#include <bits/stdc++.h>
#define MAXN 20

using namespace std;

typedef long long ll;

int n;
int costs_add[MAXN + 5], costs_rem[MAXN + 5];

vector<int> menu;
ll costs[(1 << MAXN) + 5];

void dijkstra() {
    fill(costs, costs + (1 << n), LLONG_MAX >> 1);
    set<pair<ll, int>> ff;
    for (auto pizza : menu) {
        ff.insert({costs[pizza] = 0, pizza});
    }

    while (!ff.empty()) {
        auto curr = ff.begin();
        ff.erase(curr);
        ll cost = curr->first;
        int pizza = curr->second;
        if (cost > costs[pizza]) {
            continue;
        }

        for (int j = 0; j < n; j++) {
            int adj = pizza ^ (1 << j);
            ll new_cost =
                cost + ((pizza & (1 << j)) ? costs_rem[j] : costs_add[j]);
            if (new_cost < costs[adj]) {
                ff.insert({costs[adj] = new_cost, adj});
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m, q;
    cin >> n >> m >> q;

    for (int i = 0; i < n; i++) {
        cin >> costs_add[i] >> costs_rem[i];
    }

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        int pizza = 0;
        for (int j = 0; j < k; j++) {
            int ingredient;
            cin >> ingredient;
            pizza |= (1 << ingredient);
        }

        menu.push_back(pizza);
    }

    dijkstra();

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        int pizza = 0;
        for (int j = 0; j < k; j++) {
            int ingredient;
            cin >> ingredient;
            pizza |= (1 << ingredient);
        }

        cout << costs[pizza] << "\n";
    }
}
