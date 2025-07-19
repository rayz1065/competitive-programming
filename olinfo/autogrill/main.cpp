#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

set<ll> values;

void inizia() { return; }

void apri(long long p) { values.insert(p); }

void chiudi(long long p) { values.erase(p); }

long long chiedi(long long p) {
    if (values.size() == 0) {
        return -1;
    }
    auto ub = values.upper_bound(p);
    ll next = ub == values.end() ? LLONG_MAX >> 1 : *ub;
    ll prev = ub == values.begin() ? LLONG_MAX >> 1 : *(--ub);
    ll min_dist = min(abs(p - next), abs(p - prev));
    return p + min_dist == next ? next : prev;
}
