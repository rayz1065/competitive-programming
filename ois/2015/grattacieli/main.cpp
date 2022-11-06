#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int heights[MAXN];

int main () {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    int max_height = *max_element(heights, heights + n);
    heights[n] = max_height; // dummy final height
    int l = 0, curr = -1, s = 0;
    for (int i = 0; i <= n; i++) {
        if (heights[i] == max_height) {
            if (curr != -1) {
                s = max(s, min(n - 1, i) - l + 1);
                l = curr;
            }
            curr = i;
        }
    }
    cout << s << "\n";
}
