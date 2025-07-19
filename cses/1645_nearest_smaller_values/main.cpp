#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
int values[MAXN];
int results[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    vector<pair<int, int>> answers;
    answers.push_back({INT_MIN >> 1, 0});
    for (int i = 0; i < n; i++) {
        pair<int, int> searched = {values[i], -1};
        auto found = lower_bound(answers.begin(), answers.end(), searched);
        found--;
        results[i] = found->second;
        while (values[i] <= answers.rbegin()->first) {
            answers.pop_back();
        }
        answers.push_back({values[i], i + 1});
    }

    for (int i = 0; i < n; i++) {
        cout << results[i] << " \n"[i + 1 == n];
    }
}
