#include <bits/stdc++.h>
#define MAXN 100005
#define MAXM 200005
#pragma GCC optimize("O3")

using namespace std;

int n_types;
int m_recipes;
vector<vector<int>> recipe;
vector<int> recipe_res;
long long int dist[MAXN];
vector<int> required_for[MAXN];
int missing_ingredients[MAXM];

long long int recipe_cost (int i) {
    long long int s = 1;
    for (auto j: recipe[i]) {
        s+= dist[j];
    }
    return s;
}

void dijkstra () {
    set<pair<long long int, int>> ff;
    fill(dist, dist + n_types, LLONG_MAX >> 1);
    for (int i = 0; i < m_recipes; i++) {
        if (missing_ingredients[i] == 0) {
            // no missing ingredients, can be made right away
            dist[recipe_res[i]] = 1;
            ff.insert({ 1, recipe_res[i]});
        }
    }

    while (!ff.empty()) {
        auto curr = ff.begin();
        int node = curr->second;
        ff.erase(curr);

        // this is the cheapeast price for this recipe
        for (auto j: required_for[node]) {
            missing_ingredients[j]--;
            if (missing_ingredients[j] == 0) {
                long long int curr_cost = recipe_cost(j);
                if (curr_cost < dist[recipe_res[j]]) {
                    // this is cheaper
                    auto to_erase = ff.find({ dist[recipe_res[j]], recipe_res[j] });
                    if (to_erase != ff.end()) {
                        ff.erase(to_erase);
                    }
                    dist[recipe_res[j]] = curr_cost;
                    ff.insert({ curr_cost, recipe_res[j] });
                }
            }
        }
    }
}

long long smaltisci(int n_types, int m_recipes, vector<int> recipe_res, vector<vector<int>> recipe) {
    ::n_types = n_types;
    ::m_recipes = m_recipes;
    ::recipe_res = recipe_res;
    ::recipe = recipe;

    for (int i = 0; i < m_recipes; i++) {
        for (auto ingredient: recipe[i]) {
            required_for[ingredient].push_back(i);
        }
        missing_ingredients[i] = recipe[i].size();
    }

    dijkstra();

    return dist[0];
}
