#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int almonds[MAXN];
int differences[MAXN];

struct SliceInfo {
    int difference;
    int i;

    bool operator < (const SliceInfo &other) const {
        return this->difference > other.difference;
    }
};

int main() {
#ifndef DEBUG
    fstream cin, cout;
    cin.open("input.txt", ios::in);
    cout.open("output.txt", ios::out);
#endif
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> almonds[i];
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        differences[i] = x - almonds[i];
        if (i > 0) differences[i] += differences[i - 1];
    }
    vector<SliceInfo> slices;
    slices.push_back({ 0, 0 });
    int biggest_slice = 1;
    for (int i = 0; i < n; i++) {
        SliceInfo curr = { differences[i], i + 1 };
        auto res = lower_bound(slices.begin(), slices.end(), curr); // has difference lower or equal
        if (res != slices.end()) {
            // no point adding this one
            biggest_slice = max(biggest_slice, i - res->i + 1);
            // cout << "form a slice from " << res->i << " to " << i << "\n";
        } else {
            slices.push_back(curr);
        }
    }
    cout << biggest_slice << "\n";
}
