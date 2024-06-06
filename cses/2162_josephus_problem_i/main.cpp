#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, k = 2;
    cin >> n;

    set<int> free;
    for (int i = 0; i < n; i++) {
        free.insert(i);
    }

    auto curr = free.end();
    curr--;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k % free.size(); j++) {
            curr++;
            if (curr == free.end()) {
                curr = free.begin();
            }
        }

        cout << (*curr) + 1 << " \n"[i + 1 == n];
        auto memo = curr;
        if (curr == free.begin()) {
            curr = free.end();
        }
        curr--;
        free.erase(memo);
    }
}
