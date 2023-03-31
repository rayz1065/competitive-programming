#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int numbers[MAXN];

int main () {
    int n;
    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        cin >> numbers[i];
    }
    sort(numbers, numbers + 2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cout << numbers[i] << " \n"[(i + 1) % n == 0];
    }
}
