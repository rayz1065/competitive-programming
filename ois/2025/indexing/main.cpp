#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    string a, b;
    cin >> a >> b;

    string res = "";

    for (int i = 0; i < a.size() && i < b.size() && a[i] == b[i]; i++) {
        res.push_back(a[i]);
    }

    if (res.length() == a.length()) {
        res.push_back('a');
    } else if (a[res.length()] + 1 < b[res.length()]) {
        res.push_back(a[res.length()] + 1);
    } else if (res.length() + 1 < b.length()) {
        res.push_back(b[res.length()]);
    } else {
        res.push_back(a[res.length()]);
        for (int i = res.length(); i < a.length() && a[i] == 'z'; i++) {
            res.push_back('z');
        }
        res.push_back('z');
    }

    if (a < res && res < b) {
        cout << res << "\n";
    } else {
        cout << -1 << "\n";
    }
}
