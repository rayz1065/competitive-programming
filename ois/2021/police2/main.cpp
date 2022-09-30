#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int houses[MAXN];
int visit_time[MAXN];
bool visit_end[MAXN];

int dfs (int node, int &curr_time) {
    if (visit_time[node]) {
        if (visit_end[node]) {
            return 0;
        }
        return curr_time - visit_time[node] + 1;
    }
    visit_time[node] = ++curr_time;
    int dist = dfs(houses[node], curr_time);
    visit_end[node] = curr_time;
    return dist;
}

int main () {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> houses[i];
    }

    int max_dist = 0, curr_time = 0;
    for (int i = 0; i < n; i++) {
        if (!visit_time[i]) {
            int dist = dfs(i, curr_time);
            max_dist = max(max_dist, dist);
        }
    }
    cout << max_dist << "\n";
}