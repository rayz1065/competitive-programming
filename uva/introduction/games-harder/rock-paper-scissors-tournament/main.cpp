#include <bits/stdc++.h>

#include <iomanip>

using namespace std;

int n, k;
int losses[105], wins[105];

int move_to_num(string move) {
    if (move == "rock") {
        return 0;
    } else if (move == "paper") {
        return 1;
    } else if (move == "scissors") {
        return 2;
    }
    assert(false);
}

void solve() {
    fill(wins, wins + n, 0);
    fill(losses, losses + n, 0);

    for (int i = 0; i < k * n * (n - 1) / 2; i++) {
        int player_a, player_b;
        string move_a, move_b;
        cin >> player_a >> move_a >> player_b >> move_b;
        player_a -= 1, player_b -= 1;

        int sign_a = move_to_num(move_a), sign_b = move_to_num(move_b);
        if ((sign_a + 1) % 3 == sign_b) {
            wins[player_b] += 1;
            losses[player_a] += 1;
        } else if ((sign_b + 1) % 3 == sign_a) {
            wins[player_a] += 1;
            losses[player_b] += 1;
        }
    }
}

int main() {
    cout << fixed;
    cout << setprecision(3);

    int tc = 0;
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        cin >> k;
        solve();

        if (tc == 0) {
            tc = 1;
        } else {
            cout << "\n";
        }
        for (int i = 0; i < n; i++) {
            if (wins[i] + losses[i] == 0) {
                cout << "-\n";
            } else {
                double winrate = (double)wins[i] / (wins[i] + losses[i]);
                cout << winrate << "\n";
            }
        }
    }
}
