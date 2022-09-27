#include <bits/stdc++.h>

#define MAXN 500005

using namespace std;

int n_nodes, m_branches;
int colors[MAXN];
int other_colors[MAXN];
int other_colors_dist[MAXN];
vector<int> graph[MAXN];

bool set_other_color (int node, int color, int dist) {
    // cout << "coloring " << node << " in " << color << " with dist " << dist << " instead of " << other_colors[node] << "\n";
    if (other_colors[node] == -1) {
        other_colors[node] = color;
        other_colors_dist[node] = dist;
        return true;
    }
    if (other_colors[node] == color) {
        assert (other_colors_dist[node] <= dist);
        return true;
    }
    assert (colors[node] != color);
    return false;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int n_nodes, m_branches;
    cin >> n_nodes >> m_branches;

    for (int i = 0; i < n_nodes; i++) {
        cin >> colors[i];
    }
    fill(other_colors, other_colors + n_nodes, -1);

    for (int i = 0; i < m_branches; i++) {
        int a, b;
        cin >> a >> b;

        if (colors[a] != colors[b]) {
            bool finished = false;
            finished = finished || !set_other_color(b, colors[a], 1);
            finished = finished || !set_other_color(a, colors[b], 1);

            if (finished) {
                // special case
                cout << 2 << "\n";
                return 0;
            }
        } else {
            graph[b].push_back(a);
            graph[a].push_back(b);
        }
    }

    // find multi-colored nodes
    queue<int> ff;
    for (int i = 0; i < n_nodes; i++) {
        if (other_colors[i] != -1) {
            ff.push(i);
        }
    }

    // bfs
    while (!ff.empty()) {
        int node = ff.front();
        ff.pop();

        for (auto i: graph[node]) {
            // check if the node has two colors...
            if (other_colors[i] != -1) {
                if (other_colors[node] != other_colors[i]) {
                    // this is the solution
                    // cout << "found it, between " << node << " and " << i << "\n";
                    // cout << "oc " << node << " = " << other_colors[node] << " at dist " << other_colors_dist[node] << "\n";
                    // cout << "oc " << i << " = " << other_colors[i] << " at dist " << other_colors_dist[i] << "\n";
                    cout << other_colors_dist[node] + other_colors_dist[i] + 1 << "\n";
                    return 0;
                }
                // there are only 2 shared colors, not useful
            } else {
                // we can add a color to the new node we encountered
                set_other_color(i, other_colors[node], other_colors_dist[node] + 1);
                ff.push(i);
            }
        }
    }

    // no solution found
    cout << -1 << "\n";
    return 0;
}
