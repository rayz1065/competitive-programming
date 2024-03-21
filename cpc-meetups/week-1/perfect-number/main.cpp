#include <bits/stdc++.h>

using namespace std;

bool is_perfect(int x) {
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum == 10;
}

int find_kth_perfect(int k) {
    int i = 0;
    int x = 0;
    while (i < k) {
        x++;
        if (is_perfect(x)) {
            i++;
        }
    }
    return x;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int k;
    cin >> k;
    cout << find_kth_perfect(k) << "\n";
    return 0;
}
