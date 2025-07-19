#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n, k;
pair<int, int> movies[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> movies[i].first >> movies[i].second;
        movies[i].second--;
    }
    sort(movies, movies + n);

    int res = 0;
    multiset<int> members;
    for (int i = 0; i < n; i++) {
        int t = movies[i].first, end_t = movies[i].second;
        while (!members.empty() && *members.begin() < t) {
            members.erase(members.begin());
        }
        if (members.size() < k) {
            members.insert(end_t);
            res += 1;
        } else {
            auto best = members.rbegin();
            if (*best > end_t) {
                members.erase(members.find(*best));
                members.insert(end_t);
            }
        }
    }

    cout << res << "\n";
}
