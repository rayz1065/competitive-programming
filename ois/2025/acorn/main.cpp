#include <bits/stdc++.h>

using namespace std;

pair<int, int> move(int x, int y) {
    bool swapped = x < y;
    if (swapped) {
        swap(x, y);
    }
    if (y % 2 == 0) {
        x = y + 1;
    } else {
        x = y - 1;
    }
    if (swapped) {
        swap(x, y);
    }
    cout << x << " " << y << "\n";
    cout.flush();
    return {x, y};
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int x, y;
    cin >> x >> y;

    bool win = abs(x - y) != 1 || min(x, y) % 2 == 1;
    cout << (win ? 'C' : 'N') << "\n";
    cout.flush();

    if (win) {
        tie(x, y) = move(x, y);
    }

    while (x + y > 1) {
        cin >> x >> y;
        tie(x, y) = move(x, y);
    }
}
