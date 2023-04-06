#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n;
int numbers[MAXN];

int magic_sort () {
    int s = 0;
    for (int i = 0; i < n; i++) {
        while (numbers[i] != i) {
            swap(numbers[i], numbers[numbers[i]]);
            s += 1;
        }
    }
    return s;
}

int gcd (int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int valid_distances () {
    int s = 0;
    for (int i = 0; i < n; i++) {
        int curr = abs(numbers[i] - i);
        if (curr != 0) {
            s = gcd(curr, s);
        }
    }
    return s;
}

int main () {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
        numbers[i]--;
    }
    int valid_dist = valid_distances();
    int min_swaps = magic_sort();
    for (int i = 1; i <= n; i++) {
        bool solved = valid_dist % i == 0;
        cout << (solved ? min_swaps : -1) << " ";
    }
    cout << "\n";
}
