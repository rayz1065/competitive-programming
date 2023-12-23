#include <bits/stdc++.h>
#define MAXN 100005
#define MAXC 100005

using namespace std;

typedef long long ll;

int n;
int nodes[MAXN][3];
int neighbors[MAXN][3][2];  // 0 -> coord - 1, 1 -> coord + 1
short memo[MAXN][27];       // 0 -> unknown, 1 -> false, 2 -> true
unordered_map<ll, int> node_indexes;
struct {
    int j;
    int coord;
    int left_child;
    int right_child;
    int coord_ranges[3][2];
    bool is_node;
} spacial_tree[MAXN * 2];
int free_spacial_tree_node = 0;

ll hash_node(int coords[]) {
    return ((ll)coords[0] * MAXC + coords[1]) * MAXC + coords[2];
}

bool spacial_tree_is_node(int node) {
    for (int j = 0; j < 3; j++) {
        if (spacial_tree[node].coord_ranges[j][0] !=
            spacial_tree[node].coord_ranges[j][1]) {
            return false;
        }
    }

    return true;
}

void build_spacial_tree(int node, vector<int> &indexes) {
    for (int j = 0; j < 3; j++) {
        spacial_tree[node].coord_ranges[j][0] = MAXC;
        spacial_tree[node].coord_ranges[j][1] = -1;
    }
    for (auto i : indexes) {
        for (int j = 0; j < 3; j++) {
            spacial_tree[node].coord_ranges[j][0] =
                min(spacial_tree[node].coord_ranges[j][0], nodes[i][j]);
            spacial_tree[node].coord_ranges[j][1] =
                max(spacial_tree[node].coord_ranges[j][1], nodes[i][j]);
        }
    }

    spacial_tree[node].is_node = spacial_tree_is_node(node);
    if (spacial_tree[node].is_node) {
        return;
    }

    int best_coord = -1, best_j = -1, best_split = 0;

    // find the best split
    for (int j = 0; j < 3; j++) {
        // split on the median of this coordinate
        vector<int> coords;
        coords.reserve(indexes.size());
        for (auto i : indexes) {
            coords.push_back(nodes[i][j]);
        }

        auto median = coords.begin() + coords.size() / 2;
        nth_element(coords.begin(), median, coords.end());

        int split_coord = *median;

        int before_median = 0;
        int median_freq = 0;
        for (int i = 0; i < coords.size(); i++) {
            before_median += coords[i] < split_coord;
            median_freq += coords[i] == split_coord;
        }

        if (before_median == 0) {
            before_median += median_freq;
            split_coord += 1;
        }

        int split_score =
            min(before_median, (int)coords.size() - before_median);
        if (split_score > best_split) {
            best_coord = split_coord, best_j = j, best_split = split_score;
        }
    }

    // split into the two groups
    spacial_tree[node].coord = best_coord;
    spacial_tree[node].j = best_j;
    spacial_tree[node].left_child = free_spacial_tree_node++;
    spacial_tree[node].right_child = free_spacial_tree_node++;

    vector<int> indexes_left, indexes_right;
    for (auto i : indexes) {
        if (nodes[i][best_j] < best_coord) {
            indexes_left.push_back(i);
        } else {
            indexes_right.push_back(i);
        }
    }

    build_spacial_tree(spacial_tree[node].left_child, indexes_left);
    build_spacial_tree(spacial_tree[node].right_child, indexes_right);
}

bool spacial_tree_find(int node, int root_coords[], int delta_coords[]) {
    // find a vertex in root_coords going in direction delta_coords

    // check if we're completely outside
    for (int j = 0; j < 3; j++) {
        int min_coord = root_coords[j];
        int max_coord = root_coords[j] + delta_coords[j] * MAXC;
        if (min_coord > max_coord) {
            swap(min_coord, max_coord);
        }

        if (max_coord < spacial_tree[node].coord_ranges[j][0]) {
            return false;
        }
        if (min_coord > spacial_tree[node].coord_ranges[j][1]) {
            return false;
        }
    }

    if (spacial_tree[node].is_node) {
        return true;
    }

    return spacial_tree_find(spacial_tree[node].left_child, root_coords,
                             delta_coords) ||
           spacial_tree_find(spacial_tree[node].right_child, root_coords,
                             delta_coords);
}

bool has_vertex_in_direction(int vertex, int delta_coords[]) {
    int root_coords[] = {nodes[vertex][0] + delta_coords[0],
                         nodes[vertex][1] + delta_coords[1],
                         nodes[vertex][2] + delta_coords[2]};

    return spacial_tree_find(0, root_coords, delta_coords);
}

bool solve(int vertex, int delta_coords[]) {
    int delta = ((delta_coords[0] + 1) * 3 + (delta_coords[1] + 1)) * 3 +
                (delta_coords[2] + 1);
    // cerr << "visiting " << vertex << ", " << delta_coords[0] << ","
    //      << delta_coords[1] << "," << delta_coords[2] << "\n";
    if (delta == 27 / 2) {
        return true;  // 0,0,0
    }
    if (memo[vertex][delta] != 0) {
        return memo[vertex][delta] - 1;
    }
    if (!has_vertex_in_direction(vertex, delta_coords)) {
        // visited all
        memo[vertex][delta] = true + 1;
        return true;
    }

    // cerr << "there are more vertices here...\n";

    // apply deterministic walk
    for (int j = 0; j < 3; j++) {
        if (delta_coords[j] == 0) {
            continue;
        }

        // -1 gets mapped to 0, +1 gets mapped to 1
        int new_vertex = neighbors[vertex][j][(delta_coords[j] + 1) / 2];
        if (new_vertex == -1) {
            continue;
        }

        // go to the next vertex, visit everything
        if (!solve(new_vertex, delta_coords)) {
            memo[vertex][delta] = false + 1;
            // cerr << "bad1 for " << vertex << "\n";
            return false;
        }

        // must also visit the perpendicular slice
        int new_delta_coords[] = {delta_coords[0], delta_coords[1],
                                  delta_coords[2]};
        new_delta_coords[j] = 0;
        if (!solve(new_vertex, new_delta_coords)) {
            // cerr << "bad2 for " << vertex << "\n";
            memo[vertex][delta] = false + 1;
            return false;
        }

        memo[vertex][delta] = true + 1;
        return true;
    }

    // got stuck
    // cerr << "got stuck at " << vertex << "\n";
    memo[vertex][delta] = false + 1;
    return false;
}

bool solve_all() {
    for (int i = 0; i < n; i++) {
        for (int delta = 0; delta < 27; delta++) {
            int delta_coords[] = {(delta / 9) - 1, ((delta % 9) / 3) - 1,
                                  (delta % 3) - 1};

            if (!solve(i, delta_coords)) {
                cerr << "from " << i << " cannot visit " << delta_coords[0]
                     << "," << delta_coords[1] << "," << delta_coords[2]
                     << "\n";
                return false;
            }
        }
    }

    return true;
}

void find_neighbors() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            int new_coords[] = {nodes[i][0], nodes[i][1], nodes[i][2]};
            new_coords[j] -= 1;
            ll new_key = hash_node(new_coords);
            auto new_index = node_indexes.find(new_key);
            int new_i =
                new_index == node_indexes.end() ? -1 : new_index->second;
            neighbors[i][j][0] = new_i;

            new_coords[j] += 2;
            new_key = hash_node(new_coords);
            new_index = node_indexes.find(new_key);
            new_i = new_index == node_indexes.end() ? -1 : new_index->second;
            neighbors[i][j][1] = new_i;
        }
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < n; i++) {
            cin >> nodes[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        node_indexes[hash_node(nodes[i])] = i;
    }

    vector<int> indexes;
    for (int i = 0; i < n; i++) {
        indexes.push_back(i);
    }

    build_spacial_tree(free_spacial_tree_node++, indexes);
    find_neighbors();

    cout << (solve_all() ? "YES" : "NO") << "\n";
}
