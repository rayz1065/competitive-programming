#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int suit_by_size[MAXN];
vector<long long> suits;

bool suit_cmp(int i, int j) {
    return suits[i] < suits[j];
}

vector<long long> calcola(int T, int M, vector<long long> souveniers, vector<long long> suits) {
    ::suits = suits;
    for (int i = 0; i < M; i++) {
        suit_by_size[i] = i;
    }
    sort(suit_by_size, suit_by_size + M, suit_cmp);

    int next_souv = 1;
    long long used_cap = 0;
    long long souv_brought = souveniers[0];

    vector<long long> R(M);
    for (int i = 0; i < M; i++) {
        while (next_souv < T) {
            long long can_hold = min(souveniers[next_souv], (suits[suit_by_size[i]] - used_cap) / next_souv);
            // cout << i << "\t" << suits[suit_by_size[i]] << " can hold " << can_hold << " of " << next_souv << "\n";
            souveniers[next_souv] -= can_hold;
            souv_brought += can_hold;
            used_cap += can_hold * next_souv;
            if (souveniers[next_souv]) {
                break;
            }
            next_souv++;
        }
        R[suit_by_size[i]] = souv_brought;
    }

    return R;
}
