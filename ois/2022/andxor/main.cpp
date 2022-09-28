#include <bits/stdc++.h>
#define MAXN 200005
#define MAXB 31

using namespace std;

int n_values;
int values[MAXN];
int bit_freq[MAXB];
int bit_xors[MAXB];

void set_value (int i, int new_val) {
    // remove previous value
    int prev_val = values[i];
    for (int j = 0; j < MAXB; j++) {
        if (prev_val & (1 << j)) {
            // this bit was in the previous value
            bit_freq[j]--;
            bit_xors[j]^= prev_val;
        }
    }
    values[i] = new_val;
    for (int j = 0; j < MAXB; j++) {
        if (new_val & (1 << j)) {
            // this bit is in the current value
            bit_freq[j]++;
            bit_xors[j]^= new_val;
        }
    }
}

int curr_sol () {
    int best = -1;
    for (int j = 0; j < MAXB; j++) {
        if (bit_freq[j] > 0) {
            // cout << "For " << j << " there are " << bit_freq[j] << " - " << (bit_xors[j] == 0) << "\n";
            best = max(best, bit_freq[j] - (bit_xors[j] == 0));
        }
    }
    return best;
}

int main () {
    int q_queries;
    cin >> n_values >> q_queries;
    for (int i = 0; i < n_values; i++) {
        int v;
        cin >> v;
        set_value(i, v);
    }

    cout << curr_sol() << "\n";
    while(q_queries--) {
        int i, v;
        cin >> i >> v;
        i--;
        set_value(i, v);
        cout << curr_sol() << "\n";
    }
}
