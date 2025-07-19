#include <bits/stdc++.h>

using namespace std;

const int n = 20;

void tc() {
    vector<int> waiting(n, -1);
    vector<int> original_pos;
    for (int i = 0;; i++) {
        int pos;
        cin >> pos;
        if (pos == 99) {
            break;
        }
        pos--;
        waiting[pos] = i;
        original_pos.push_back(pos);
    }

    int n_waiting = original_pos.size();

    vector<int> vacated;
    char buf[10];
    cin.getline(buf, 10);

    while (true) {
        if (!(cin.getline(buf, 10))) {
            break;
        } else if (strlen(buf) == 0) {
            break;
        }

        int pos;
        sscanf(buf, "%d", &pos);
        pos--;
        vacated.push_back(pos);
    }

    vector<int> results(n_waiting, -1);
    for (auto pos : vacated) {
        int movement = 0;
        for (; movement < n && waiting[(pos + n - movement) % n] == -1;
             movement++);
        if (movement == n) {
            break;
        }
        vector<int> tmp = waiting;
        for (int i = 0; i < n; i++) {
            waiting[i] = tmp[(i + n - movement) % n];
        }
        results[waiting[pos]] = pos;
        waiting[pos] = -1;
    }

    for (int i = 0; i < n_waiting; i++) {
        cout << "Original position " << original_pos[i] + 1 << " ";
        if (results[i] == -1) {
            cout << "did not park\n";
        } else {
            cout << "parked in " << results[i] + 1 << "\n";
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        tc();
        if (t) {
            cout << "\n";
        }
    };
}
