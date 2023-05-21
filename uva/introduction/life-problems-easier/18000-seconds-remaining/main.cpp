#include <bits/stdc++.h>

using namespace std;

vector<int> read_transfers (int remaining) {
    vector<int> s;
    while (remaining > 0) {
        int transfer;
        cin >> transfer;
        remaining -= transfer;
        s.push_back(transfer);
    }
    return s;
}

void solve (int remaining) {
    auto transfers = read_transfers(remaining);
    int buckets = transfers.size() / 5;

    for (int i = 0; i < buckets * 5; i += 5) {
        int current_upload = 0;
        for (int j = i; j < i + 5; j++) {
            current_upload += transfers[j];
        }
        remaining -= current_upload;

        if (current_upload == 0) {
            cout << "   Time remaining: stalled\n";
        } else {
            int remaining_time = ceil(5. * remaining / current_upload);
            cout << "   Time remaining: " << remaining_time << " seconds\n";
        }
    }
    cout << "Total time: " << transfers.size() << " seconds\n\n";
}

int main () {
    int tc = 0;
    while (true) {
        tc += 1;
        int remaining;
        cin >> remaining;

        if (remaining == 0) {
            break ;
        }

        cout << "Output for data set " << tc << ", " << remaining << " bytes:\n";
        solve(remaining);
    }
}
