#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long ll;

int n;
pair<int, int> locations[MAXN * 2];
int xs[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> xs[i];
    }
    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;
        int left = xs[i] - r, right = xs[i] + r;
        locations[i * 2] = {left, r};
        locations[i * 2 + 1] = {right, -r};
    }

    sort(locations, locations + 2 * n);
    locations[2 * n] = {INT_MAX >> 1, 0};  // dummy

    ll res = 0;
    multiset<int> curr_heights;
    int previous_location = -1;

    for (int i = 0; i < 2 * n;) {
        int curr_location = locations[i].first;
        res += 2 * (ll)(-*curr_heights.begin()) *
               (curr_location - previous_location);

        while (locations[i].first == curr_location) {
            if (locations[i].second < 0) {
                curr_heights.erase(curr_heights.find(locations[i].second));
            } else {
                curr_heights.insert(-locations[i].second);
            }
            i += 1;
        }

        previous_location = curr_location;
    }

    cout << res << "\n";
}
