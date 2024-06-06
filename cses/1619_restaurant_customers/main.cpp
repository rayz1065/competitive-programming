#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
int arrival_times[MAXN], leave_times[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arrival_times[i] >> leave_times[i];
    }

    sort(arrival_times, arrival_times + n);
    sort(leave_times, leave_times + n);

    int best = 0;
    for (int i = 0, j = 0; i < n; i++) {
        // current time: arrival_times[i]
        for (; leave_times[j] < arrival_times[i]; j++);
        best = max(best, i - j + 1);
    }

    cout << best << "\n";
}
