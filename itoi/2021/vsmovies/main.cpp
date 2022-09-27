#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 500005
#define MAXS 100005

using namespace std;

int s_superheros, n_movies;
struct Movie {
    int a;
    int b;
    int len;
} movies[MAXN];
vector<Movie> mst[MAXS];
int movies_order[MAXN];
int dsu_parent[MAXS];
int dsu_rank[MAXS];
int lca_ancestors[MAXS][20];
int lca_max_weight[MAXS][20];
int lca_depth[MAXS];

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

void lca_dfs (int node) {
    for (auto movie: mst[node]) {
        int other = movie.a == node ? movie.b : movie.a;
        if (other != lca_ancestors[node][0]) {
            // not the direct parent
            lca_ancestors[other][0] = node;
            lca_max_weight[other][0] = movie.len;
            lca_depth[other] = lca_depth[node] + 1;
            lca_dfs(other);
        }
    }
}

pair<int, int> get_lca (int a, int b) {
    int max_w = -1;

    // make the depths equal
    if (lca_depth[b] < lca_depth[a]) {
        // make b the deepest node
        swap(a, b);
    }
    for (int k = 19; k >= 0; k--) {
        int anc_dist = 1 << k; // 2 ** k
        int curr_dist = lca_depth[b] - lca_depth[a];
        if (anc_dist <= curr_dist) {
            max_w = max(max_w, lca_max_weight[b][k]);
            b = lca_ancestors[b][k];
        }
    }

    if (a == b) {
        // a was a parent of b
        return { max_w, a };
    }

    for (int k = 19; k >= 0; k--) {
        if (lca_ancestors[a][k] != lca_ancestors[b][k]) {
            max_w = max(max_w, lca_max_weight[a][k]);
            max_w = max(max_w, lca_max_weight[b][k]);
            a = lca_ancestors[a][k];
            b = lca_ancestors[b][k];
        }
    }
    // assert(lca_ancestors[a][0] == lca_ancestors[b][0]);
    max_w = max(max_w, lca_max_weight[a][0]);
    max_w = max(max_w, lca_max_weight[b][0]);
    return { max_w, lca_ancestors[a][0] };
}

void compute_lca_ancestors () {
    // visit the mst and find the 2**k ancestors of each node
    for (int i = 0; i < s_superheros; i++) {
        fill(lca_ancestors[i], lca_ancestors[i] + 20, -1);
    }

    lca_dfs(0);

    for (int k = 1; k < 20; k++) {
        for (int i = 0; i < s_superheros; i++) {
            // distance = 2 ** k
            int ancestor = lca_ancestors[i][k - 1]; // 2 ** (k - 1)
            if (ancestor == -1) {
                continue ;
            }
            int ancestor_w = lca_max_weight[i][k - 1];
            int ancestor_ancestor = lca_ancestors[ancestor][k - 1]; // 2 ** k
            if (ancestor_ancestor == -1) {
                continue ;
            }
            int anc_anc_w = lca_max_weight[ancestor][k - 1];
            lca_ancestors[i][k] = ancestor_ancestor;
            lca_max_weight[i][k] = max(ancestor_w, anc_anc_w);
        }
    }
#ifdef DEBUG
    for (int i = 0; i < s_superheros; i++) {
        cout << i << " ->\t";
        for (int k = 0; k < 3; k++) {
            cout << lca_max_weight[i][k] << "(" << lca_ancestors[i][k] << ") ";
        }
        cout << "\n";
    }

    cout << "\t";
    for (int j = 0; j < s_superheros; j++) {
        cout << j << "\t";
    }
    cout << "\n";
    for (int i = 0; i < s_superheros; i++) {
        cout << i << "\t";
        for (int j = 0; j < s_superheros; j++) {
            auto lca_info = get_lca(i, j);
            cout << lca_info.first << "(" << lca_info.second << ")\t";
        }
        cout << "\n";
    }
    cout << "\n";
#endif
}

bool movie_lt (int i, int j) {
    return movies[i].len < movies[j].len;
}

int dsu_get_parent (int i) {
    if (dsu_parent[i] == i) {
        return i;
    }
    return dsu_parent[i] = dsu_get_parent(dsu_parent[i]);
}

void dsu_merge (int i, int j) {
    i = dsu_get_parent(i);
    j = dsu_get_parent(j);
    if (dsu_rank[i] < dsu_rank[j]) {
        // make j the parent
        dsu_parent[i] = j;
    } else if (dsu_rank[i] > dsu_rank[j]) {
        // make i the parent
        dsu_parent[j] = i;
    } else {
        // make j the parent and increase its rank
        dsu_parent[i] = j;
        dsu_rank[j]++;
    }
}

/**
 * returns weight of mst
 */
long long compute_mst () {
    for (int i = 0; i < n_movies; i++) {
        movies_order[i] = i;
    }
    for (int i = 0; i < s_superheros; i++) {
        dsu_parent[i] = i;
    }
    sort(movies_order, movies_order + n_movies, movie_lt);

    long long s = 0;
    for (int i = 0; i < n_movies; i++) {
        int movie_id = movies_order[i];
        auto movie = movies[movie_id];
        int a = movie.a;
        int b = movie.b;
        if (dsu_get_parent(a) != dsu_get_parent(b)) {
            dsu_merge(a, b);
            mst[a].push_back(movie);
            mst[b].push_back(movie);
            s += movie.len;
        }
    }
    return s;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    n_movies = fastin();
    s_superheros = fastin();
    for (int i = 0; i < n_movies; i++) {
        movies[i].a = fastin();
        movies[i].b = fastin();
        movies[i].len = fastin();
    }
    long long mst_weight = compute_mst();
    compute_lca_ancestors();

    for (int i = 0; i < n_movies; i++) {
        auto movie = movies[i];
        // remove the heaviest weight linking these movies
        int heaviest = get_lca(movie.a, movie.b).first;
        cout << mst_weight - heaviest + movie.len << "\n";
    }
}
