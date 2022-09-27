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
int movies_order[MAXN];
int dsu_parent[MAXS];

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
    dsu_parent[i] = j;
}

/**
 * returns weight of mst
 */
long long compute_mst () {
    sort(movies_order, movies_order + n_movies, movie_lt);

    long long s = 0;
    for (int i = 0; i < n_movies; i++) {
        int movie_id = movies_order[i];
        auto movie = movies[movie_id];
        int a = movie.a;
        int b = movie.b;
        if (dsu_get_parent(a) != dsu_get_parent(b)) {
            dsu_merge(a, b);
            s += movie.len;
        }
    }
    return s;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n_movies >> s_superheros;
    for (int i = 0; i < n_movies; i++) {
        cin >> movies[i].a >> movies[i].b >> movies[i].len;
    }
    long long mst_weight = compute_mst();

    for (int i = 0; i < n_movies; i++) {
        for (int i = 0; i < n_movies; i++) {
            movies_order[i] = i;
        }
        for (int i = 0; i < s_superheros; i++) {
            dsu_parent[i] = i;
        }
        dsu_merge(movies[i].a, movies[i].b);
        cout << compute_mst() + movies[i].len << "\n";
    }
}
