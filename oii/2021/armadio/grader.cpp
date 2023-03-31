#include <iostream>
#include <vector>
using namespace std;

void evadi(int Q, vector<int>& N);

int main() {
    cin.exceptions(istream::failbit);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    vector<int> N(Q);
    for (int& i : N) {
        cin >> i;
    }

    evadi(Q, N);

    for (int i = 0; i < Q; i++) {
      cout << N[i] << " ";
    }
    cout << endl;

    return 0;
}
