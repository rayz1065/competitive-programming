#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

tuple<char, ll, ll> prisonier(ll W, vector<ll> notebook) {
    if (W == 0) {
        // counter
        return {'w', 1, 0};  // odd
    } else if (!notebook.empty() && notebook[0] == 0) {
        // counter, future loops
        if (notebook.size() == 10) {
            // output
            int res = 0;
            for (int i = 1; i < notebook.size(); i++) {
                res += notebook[i] * (1 << (i - 1));
            }
            res += (W == 1) * (1 << (notebook.size() - 1));
            return {'a', res, 0};
        }
        int bit = (W + 1) / 2;
        return {'w', -1, bit};  // bit 0 on blackboard
    }

    // regular
    bool all_even = true;
    for (auto i : notebook) {
        all_even = all_even && i == -1;
    }

    int res = all_even ? -W : W;

    return {'w', res, res};
}

#ifdef DEBUG
int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<ll>> notebooks(n);
    ll W = 0;

    while (true) {
        for (int i = 0; i < n; i++) {
            ll note, new_w;
            char op;
            tie(op, new_w, note) = prisonier(W, notebooks[i]);
            if (op == 'a') {
                cout << new_w << "\n";
                // assert(new_w == n);
                return 0;
            }
            W = new_w;
            notebooks[i].push_back(note);
        }
    }
}
#endif
