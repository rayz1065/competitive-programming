#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int times[MAXN];

int main () {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> times[i];
        times[i] += i;
    }
    int delivery_time = times[0];
    int changes = 0;
    for (int i = 1; i < n; i++) {
        if (delivery_time == i) {
            break ;
        }
        if (times[i] < delivery_time) {
            delivery_time = times[i];
            changes++;
        }
    }
    cout << delivery_time << " " << changes << "\n";
}
