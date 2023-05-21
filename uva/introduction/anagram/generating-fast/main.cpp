#include <bits/stdc++.h>

using namespace std;

int main () {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;

        sort(word.begin(), word.end());

        do {
            cout << word << "\n";
        } while(next_permutation(word.begin(), word.end()));

        cout << "\n";
    }
}
