#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
vector<int> graph[MAXN];

int start_time[MAXN], low_link[MAXN], curr_time;
bool on_stack[MAXN];

stack<int> tarjan_stack;

int n_sccs;
int sccs[MAXN];

void strong_connect(int node) {
    start_time[node] = ++curr_time;
    low_link[node] = curr_time;
    tarjan_stack.push(node);
    on_stack[node] = true;

    for (auto j : graph[node]) {
        if (start_time[j] == 0) {
            strong_connect(j);
            low_link[node] = min(low_link[node], low_link[j]);
        } else if (on_stack[j]) {
            low_link[node] = min(low_link[node], start_time[j]);
        }
    }

    if (low_link[node] == start_time[node]) {
        int j = -1;
        do {
            j = tarjan_stack.top();
            tarjan_stack.pop();
            sccs[j] = n_sccs;
            on_stack[j] = false;
        } while (node != j);

        n_sccs += 1;
    }
}

void tarjan_sccs() {
    for (int i = 0; i < n; i++) {
        if (start_time[i] == 0) {
            strong_connect(i);
        }
    }
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> n >> m;

    while (m--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
    }

    tarjan_sccs();

    cout << n_sccs << "\n";
    for (int i = 0; i < n; i++) {
        cout << sccs[i] + 1 << " \n"[i + 1 == n];
    }
}
