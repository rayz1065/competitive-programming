#include <bits/stdc++.h>

using namespace std;

int main () {
    int t = 1;
    while (true) {
        string characters;
        cin >> characters;
        if (characters == "") {
            break ;
        }
        int m_queries;
        cin >> m_queries;

        set<int> zeros, ones;
        for (int i = 0; i < (int) characters.size(); i++) {
            if (characters[i] == '0') {
                zeros.insert(i);
            } else {
                ones.insert(i);
            }
        }
        zeros.insert(characters.size());
        ones.insert(characters.size());

        cout << "Case " << t++ << ":\n";

        for (int q = 0; q < m_queries; q++) {
            int i, j;
            cin >> i >> j;
            if (i > j) {
                swap(i, j);
            }

            int next_zero = *zeros.lower_bound(i);
            int next_one = *ones.lower_bound(i);

            if (next_zero > j || next_one > j) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
}
