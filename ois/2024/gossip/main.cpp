#include <bits/stdc++.h>
#define MAXN 100005
#define LOGMAXN 20

using namespace std;

int n;
int best_friend[MAXN];
int loops_count, loop_length[MAXN];
int loop_id[MAXN], distance_from_loop[MAXN];
int visited_start[MAXN];
int visited_end[MAXN];
int curr_time;

int lca_parent[MAXN][LOGMAXN];

void mark_loop(int node) {
    if (loop_id[node] != 0) {
        return;
    }
    loop_id[node] = loops_count;
    loop_length[loops_count] += 1;
    mark_loop(best_friend[node]);
}

void visit(int node) {
    assert(visited_start[node] == 0);
    visited_start[node] = ++curr_time;
    int bf = best_friend[node];

    if (visited_end[bf]) {
        // found a previous loop
        distance_from_loop[node] = distance_from_loop[bf] + 1;
        loop_id[node] = loop_id[bf];
    } else if (visited_start[bf]) {
        // found ends of loop
        loops_count += 1;
        mark_loop(node);
    } else {
        visit(bf);
        if (loop_id[node] == 0) {
            // first branch outside the loop
            loop_id[node] = loop_id[bf];
            distance_from_loop[node] = distance_from_loop[bf] + 1;
        }
    }

    visited_end[node] = curr_time;
}

void precompute() {
    for (int i = 0; i < n; i++) {
        if (loop_id[i] == 0) {
            visit(i);
        }
    }

    // for each vertex that is not in a loop, compute the lifting table
    for (int i = 0; i < n; i++) {
        lca_parent[i][0] = distance_from_loop[i] > 0 ? best_friend[i] : -1;
    }

    for (int j = 1; j < LOGMAXN; j++) {
        for (int i = 0; i < n; i++) {
            int p = lca_parent[i][j - 1];
            lca_parent[i][j] = p == -1 ? -1 : lca_parent[p][j - 1];
        }
    }
}

int get_distance(int a, int b) {
    if (loop_id[a] != loop_id[b]) {
        return -1;
    }

    if (distance_from_loop[b] > distance_from_loop[a]) {
        swap(a, b);
    }

    int res = 0;

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        int delta = 1 << j;
        int new_distance = distance_from_loop[a] - delta;
        if (new_distance >= distance_from_loop[b]) {
            a = lca_parent[a][j];
            res += delta;
        }
    }

    for (int j = LOGMAXN - 1; j >= 0; j--) {
        int pa = lca_parent[a][j];
        int pb = lca_parent[b][j];
        if (pa != pb && distance_from_loop[pa] > 0) {
            a = pa;
            b = pb;
            res += 1 << j;
        }
    }

    if (a != b && distance_from_loop[a] > 0) {
        a = lca_parent[a][0];
        b = lca_parent[b][0];
        res += 2;
    }

    if (a == b) {
        return res;
    }

    // both a and b are now in the loop
    int curr_loop_id = loop_id[a];

    int loop_distance =
        (visited_start[b] - visited_start[a] + loop_length[curr_loop_id]) %
        loop_length[curr_loop_id];
    loop_distance =
        min(loop_distance, loop_length[curr_loop_id] - loop_distance);
    res += loop_distance;

    return res;
}

int fastin() {
    int v = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = getchar_unlocked();
    }
    return v;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    n = fastin();

    for (int i = 0; i < n; i++) {
        best_friend[i] = fastin();
    }

    precompute();

    int q_queries = fastin();

    while (q_queries--) {
        int a = fastin(), b = fastin();
        cout << get_distance(a, b) << " \n"[q_queries == 0];
    }
}
