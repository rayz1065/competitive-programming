#include <bits/stdc++.h>

using namespace std;

string OPTIONS[] = {"00", "25", "50", "75"};

void get_freqs(string &n, int res[]) {
    fill(res, res + 10, 0);
    for (int i = 0; i < n.length(); i++) {
        res[n[i] - '0'] += 1;
    }
}

int solve(string &n) {
    if (n.length() < 2) {
        return -1;
    }

    int digit_freqs[10];
    get_freqs(n, digit_freqs);

    string suffix = n.substr(n.length() - 2);

    int result = 999;
    for (auto option : OPTIONS) {
        if (suffix == option) {
            return 0;
        }

        if (suffix[0] == option[1] && suffix[1] == option[0]) {
            return 1;
        }

        int distance = suffix[0] == option[0] || suffix[1] == option[1] ? 1 : 2;
        int option_freqs[10];
        get_freqs(option, option_freqs);

        bool found = true;
        for (int digit = 0; digit < 10; digit++) {
            if (digit_freqs[digit] < option_freqs[digit]) {
                found = false;
                break;
            }
        }

        if (found) {
            result = min(result, distance);
        }
    }

    return result == 999 ? -1 : result;
}

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        string n;
        cin >> n;
        cout << solve(n) << "\n";
    }
}
