#include <bits/stdc++.h>

using namespace std;

void tc() {
    int n, a, b;
    cin >> n >> a >> b;
    int original_n = n;

    bool swapped = a < b;
    if (swapped) {
        swap(a, b);
    }

    int even = n - a - b;
    n -= even;

    if ((n > 0 && b == 0) || even < 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    vector<int> moves_a, moves_b;
    for (int i = 0; i < even; i++) {
        moves_a.push_back(original_n - i);
        moves_b.push_back(original_n - i);
    }

    for (int i = 0; i < b; i++) {
        moves_a.push_back(i + 1);
        moves_b.push_back(n - b + 1 + i);
    }
    for (int i = 0; i < a; i++) {
        moves_a.push_back(n - a + 1 + i);
        moves_b.push_back(i + 1);
    }

    if (swapped) {
        swap(moves_a, moves_b);
    }

    for (int i = 0; i < moves_a.size(); i++) {
        cout << moves_a[i] << " \n"[i + 1 == moves_a.size()];
    }
    for (int i = 0; i < moves_b.size(); i++) {
        cout << moves_b[i] << " \n"[i + 1 == moves_b.size()];
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) tc();
}
