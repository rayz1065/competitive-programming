#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define MAXN 100005

using namespace std;

int n;
struct Antenna {
    int l_receiver;
    int p_power;
    int s_start;
    int t_interval;
} antennas[MAXN];
struct PowerInfo {
    int power;
    int time;

    bool operator < (const PowerInfo &other) const {
        return this->power < other.power;
    }
};
int trans_time[MAXN];

int calculate_transmit (int i, int t) {
    if (t < antennas[i].s_start) return antennas[i].s_start; // transmit right away
    if (antennas[i].t_interval == 0) return t + 1;
    int offset = t - antennas[i].s_start;
    int cycles = offset / antennas[i].t_interval + 1; // after how many cycles it transmits
    return antennas[i].s_start + cycles * antennas[i].t_interval;
}

int solve () {
    set<PowerInfo> transmit_powers; // normalized transmit powers and corresponding times
    // increasing in both transmitting power and start times
    transmit_powers.insert({ INT_MAX, INT_MAX >> 1 }); // never transmitted dummy signal
    transmit_powers.insert({ antennas[0].p_power, antennas[0].s_start });
    for (int i = 1; i < n; i++) {
        auto res = transmit_powers.lower_bound({ antennas[i].l_receiver, 0 });
        trans_time[i] = calculate_transmit(i, res->time);
        if (trans_time[i] > INT_MAX >> 1) {
            // never trasmitted
            continue ;
        }
        PowerInfo p = { antennas[i].p_power, trans_time[i] };
        res = transmit_powers.lower_bound(p);
        if (res->time > trans_time[i]) {
            // useful to add this power
            // find the ones with less power that output later
            for (res--; res != transmit_powers.begin() && res->time >= trans_time[i]; res--) {
                // res has less power and outputs later
                res = transmit_powers.erase(res);
            };
            transmit_powers.insert(p);
        }
    }
    return trans_time[n - 1] < (INT_MAX >> 1) ? trans_time[n - 1] : -1;
}

int main () {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int d_decay;
    cin >> n >> d_decay;
    for (int i = 0; i < n; i++) {
        cin >> antennas[i].l_receiver >> antennas[i].p_power
            >> antennas[i].s_start >> antennas[i].t_interval;
        antennas[i].l_receiver += d_decay * i;
        antennas[i].p_power += d_decay * i;
    }
    cout << solve() << "\n";
}
