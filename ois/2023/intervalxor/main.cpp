#include <bits/stdc++.h>

using namespace std;

void tc () {
    int number;
    cin >> number;
    int s_xor = 1 - (((number - 1) / 2) % 2);
    int rem = number;
    for (int i = 30; i > 0; i--) {
        int am = (1 << i);
        if (am <= rem) {
            rem -= am;
            if (rem % 2 == 0) {
                s_xor ^= am;
            }
        }
    }
    int added = 0;
    int max_xor = s_xor;
    for (int i = 30; i >= 0; i--) {
        int am = 1 << i;
        if ((added | am) <= number && !(max_xor & am)) {
            added |= am;
            max_xor |= am;
        }
    }
    cout << s_xor << " " << max_xor << "\n";
}

int main () {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) tc();
}