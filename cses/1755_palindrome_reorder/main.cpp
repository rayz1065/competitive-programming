#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    string letters;
    cin >> letters;
    int n = letters.length();
    sort(letters.begin(), letters.end());

    string res, center;
    int freq = 1;
    for (int i = 1; i < n; i++) {
        if (letters[i] == letters[i - 1] && freq == 1) {
            freq = 0;
            res += letters[i];
        } else if (letters[i] == letters[i - 1]) {
            freq = 1;
        } else if (freq == 1) {
            center += letters[i - 1];
            freq = 1;
        } else {
            freq = 1;
        }
    }

    if (freq == 1) {
        center += letters[n - 1];
    }

    string reversed = res;
    reverse(reversed.begin(), reversed.end());

    if (center.size() > 1) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    res += center;
    res += reversed;

    cout << res << "\n";
}
