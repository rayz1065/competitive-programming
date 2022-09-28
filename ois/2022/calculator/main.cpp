#include <bits/stdc++.h>
#define MAXN 10010
#define MAX_LSHIFT 14

using namespace std;
typedef long long int lli;

enum Operator {
    ADD,
    SUB,
    MUL,
    LSHIFT,
    DIV
};
string operator_str[] = { "+", "-", "*", "<<", "/" };

struct NodeParents {
    int op;
    int a;
    int b;
} parents[MAXN];
int dist[MAXN];
bool visited[MAXN];
set<pair<int, int>> ff;

void eval_dist (int node, int new_dist, Operator op, int a, int b) {
    if (node < MAXN && node > 0 && dist[node] > new_dist) {
        ff.insert({ new_dist, node });
        dist[node] = new_dist;
        parents[node] = { op, a, b };
    }
}

void dijkstra () {
    fill(dist, dist + MAXN, INT_MAX >> 1);
    dist[1] = 0;
    ff.insert({ 0, 1 });

    while (!ff.empty()) {
        auto curr = ff.begin();
        ff.erase(curr);
        int node = curr->second;
        if (visited[node]) {
            // already visited
            continue ;
        }
        visited[node] = true;

        for (int i = 1; i < MAXN; i++) {
            if (visited[i]) {
                int greatest = max(node, i);
                int lowest = min(node, i);
                int new_dist = dist[node] + dist[i] + 1;

                // sum
                eval_dist(i + node, new_dist, Operator::ADD, i, node);
                // sub
                eval_dist(greatest - lowest, new_dist, Operator::SUB, greatest, lowest);
                // product
                eval_dist(i * node, new_dist, Operator::MUL, i, node);

                // left shift
                if (node < MAX_LSHIFT) {
                    eval_dist((lli) i << node, new_dist, Operator::LSHIFT, i, node);
                }
                if (i < MAX_LSHIFT) {
                    eval_dist((lli) node << i, new_dist, Operator::LSHIFT, node, i);
                }

                // other bitwise operators
                // eval_dist(node | i, new_dist, "|", node, i);
                // eval_dist(node & i, new_dist, "&", node, i);
                // eval_dist(node ^ i, new_dist, "^", node, i);

                // integer division
                eval_dist(greatest / lowest, new_dist, Operator::DIV, greatest, lowest);
                // eval_dist(greatest % lowest, new_dist, "%", greatest, lowest);
            }
        }
    }
}

void print_num (int node) {
    if (node == 1) {
        cout << 1;
        return ;
    }
    cout << '(';
    print_num(parents[node].a);
    cout << operator_str[parents[node].op];
    print_num(parents[node].b);
    cout << ')';
}

int main() {
    int M;
    cin >> M;

    dijkstra();

    print_num(M);
    // for (int i = 2; i < MAXN; i++) {
    //     cout << "{" << parents[i].op << "," << parents[i].a << "," << parents[i].b << "},";
    //     if ((i - 2 + 1) % 7 == 0) {
    //         cout << "\n";
    //     }
    // }
    cout << "\n";
}
