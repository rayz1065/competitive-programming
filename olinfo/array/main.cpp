#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    int acc = 0;
    for (int i = 0; i < n; i++) {
        int curr;
        cin >> curr;
        acc += curr;
    }

    cout << acc << " " << (double) acc / n << "\n";
}