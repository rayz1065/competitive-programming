#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

pair<int, pair<bool, int>> customers[MAXN * 2];
int res[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        customers[i * 2] = {a, {0, i}};
        customers[i * 2 + 1] = {b, {1, i}};
    }

    sort(customers, customers + n * 2);

    set<int> free;
    for (int i = 0; i < n; i++) {
        free.insert(i + 1);
    }

    int required_rooms = 0;
    for (int i = 0; i < 2 * n; i++) {
        if (!customers[i].second.first) {
            int room = *free.begin();
            free.erase(free.begin());
            required_rooms = max(required_rooms, room);
            res[customers[i].second.second] = room;
        } else {
            int room = res[customers[i].second.second];
            free.insert(room);
        }
    }

    cout << required_rooms << "\n";
    for (int i = 0; i < n; i++) {
        cout << res[i] << " \n"[i + 1 == n];
    }
}
