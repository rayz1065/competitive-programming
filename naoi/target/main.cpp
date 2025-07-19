#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int disks[MAXN][15];
pair<ll, ll> ccw_move_right[MAXN][15];
pair<ll, ll> ccw_move_left[MAXN][15];
ll disk_size[MAXN];

void precompute(int i) {
    for (int j = 0; j < 10; j++) {
        disk_size[i] += disks[i][j];
    }
    ll disk_full = disk_size[i];
    ll disk_half = disk_full / 2;

    ll acc = 0;
    for (int j = 0; j < 10; j++) {
        if (disks[i][j] == 0) {
            continue;
        }

        ll min_loc = acc, max_loc = acc + disks[i][j] - 1;

        // right side relative coordinates
        ccw_move_right[i][j] = {min_loc, max_loc};
        // left side relative coordinates
        ccw_move_left[i][j] = {min_loc + disk_half, max_loc + disk_half};

        acc += disks[i][j];
    }
}

pair<ll, ll> move(pair<ll, ll> x, ll amount) {
    return {x.first + amount, x.second + amount};
}

pair<bool, pair<ll, ll>> get_overlap(pair<ll, ll> a, pair<ll, ll> b) {
    ll overlap_min = max(a.first, b.first);
    ll overlap_max = min(a.second, b.second);
    if (overlap_min > overlap_max) {
        return {false, {-1, -1}};
    }
    return {true, {overlap_min, overlap_max}};
}

ll get_min_moves(int i, int left, int right) {
    if (disks[i][left] == 0 || disks[i][right] == 0) {
        return -1;
    }

    ll disk_full = disk_size[i];

    vector<pair<pair<ll, ll>, pair<ll, ll>>> possibilities = {
        {ccw_move_right[i][right], ccw_move_left[i][left]},
        {move(ccw_move_right[i][right], disk_full), ccw_move_left[i][left]}};

    ll best = LLONG_MAX >> 1;
    for (auto poss : possibilities) {
        auto found = get_overlap(poss.first, poss.second);
        if (!found.first) {
            continue;
        }

        auto overlap = found.second;
        ll ccw_min = overlap.first;
        ll ccw_max = overlap.second;

        if ((ccw_min <= 0 && 0 <= ccw_max) ||
            (ccw_min <= disk_full && disk_full <= ccw_max)) {
            // already overlapping
            return 0;
        }

        ll move = min(abs(ccw_min), abs(ccw_max));
        ll move_2 = min(abs(ccw_min - disk_full), abs(ccw_max - disk_full));

        best = min(best, min(move, move_2));
    }

    return best == (LLONG_MAX >> 1) ? -1 : best;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> disks[i][j];
        }
        precompute(i);
    }

    int q;
    cin >> q;
    while (q--) {
        string target;
        cin >> target;
        ll moves = 0;
        bool possible = true;
        for (int i = 0; i < n; i++) {
            ll res = get_min_moves(n - i - 1, target[i] - '0',
                                   target[2 * n - i - 1] - '0');
            if (res == -1) {
                possible = false;
                break;
            }
            moves += res;
        }

        if (possible) {
            cout << "POSSIBLE\n";
            cout << moves << "\n";
        } else {
            cout << "IMPOSSIBLE\n";
            cout << -1 << "\n";
        }
    }
}
