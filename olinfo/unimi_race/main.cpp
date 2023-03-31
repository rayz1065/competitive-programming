#include <bits/stdc++.h>
#define MAXN 70000

using namespace std;

int n;
int curr_time;
struct Racer {
    int i;
    int a;
    int b;

    int y () const {
        return b * curr_time + a;
    }

    bool operator < (const Racer &other) const {
        if (this->y() == other.y()) {
            return this->i > other.i;
        }
        return this->y() > other.y();
    }
} racers[MAXN];

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        racers[i].i = i;
        cin >> racers[i].a >> racers[i].b;
    }
    while (n > 1) {
        curr_time++;
        nth_element(racers, racers + n / 2, racers + n);
        n /= 2;
    }
    cout << racers[0].i << "\n";
}