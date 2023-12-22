#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll my_round (double x) {
    ll i_part = x;
    if (x - i_part >= 0.5) {
        return i_part + 1;
    }
    return i_part;
}

int main () {
    int daily_seconds = 24 * 3600;
    int loss_a, loss_b;

    while (cin >> loss_a >> loss_b) {
        // seconds after which they sync
        double sync_time = (double) daily_seconds * daily_seconds / 2 / abs(loss_a - loss_b);

        // "a-seconds" that a moves in a second
        double speed_a = 1. - (double) loss_a / daily_seconds;

        // time according to a
        int a_time = my_round(speed_a * sync_time / 60) % daily_seconds;

        int hour = (a_time / 60) % 12;
        if (hour == 0) {
            hour = 12;
        }
        int minute = a_time % 60;
        cout << loss_a << " " << loss_b << " "
             << setfill('0') << std::setw(2) << hour << ":"
             << setfill('0') << std::setw(2) << minute << "\n";
    }
}
