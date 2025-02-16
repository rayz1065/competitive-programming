
#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n;
int values[MAXN];

void print_solution() {
    cout << "! ";
    for (int i = 0; i < n; i++) {
        cout << values[i] << " \n"[i + 1 == n];
    }
    cout.flush();
}

int prompt(int i, int j) {
    cout << "? " << i + 1 << " " << j + 1 << "\n";
    cout.flush();
    int res;
    cin >> res;
    return res;
}

void refine(int bit) {
    int j = find(values, values + n, (1 << bit)) - values;
    for (int i = 0; i < n; i++) {
        if (i == j || (values[i] & values[j]) == 0) {
            continue;
        }
        int res = prompt(i, j);
        if (res == -1) {
            values[i] -= values[j];
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n; i++) {
        int highest_bit = prompt(i, i);
        values[i] = (1 << (highest_bit + 1)) - 1;
    }

    for (int i = 0; (1 << i) < n; i++) {
        refine(i);
    }

    print_solution();
}
