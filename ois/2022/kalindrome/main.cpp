#include <bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

int n;
char s[1000005];

bool is_kalindrome (int k) {
    if (n % k != 0) {
        return false;
    }

    for (int group = 0; group < n / k; group++) {
        for (int group_offset = 0; group_offset < k; group_offset++) {
            // first position to check is simply i
            int i = group * k + group_offset;
            // the second is in the opposite group
            int group_start = n - (group + 1) * k; // which starts at

            if (s[i] != s[group_start + group_offset]) {
                return false;
            }
        }
    }
    // check passed
    return true;
}

int solve () {
    for (int i = 1; i < n; i++) {
        if (is_kalindrome(i)) {
            return i;
        }
    }
    return n;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;
    cout << solve() << "\n";
}