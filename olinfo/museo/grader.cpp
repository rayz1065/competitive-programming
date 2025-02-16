#include <iostream>
#include <vector>
using namespace std;

void inizia(int N, vector<int> A);
void aggiorna(int P, int X);
int massimo(int L, int R);

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for(int &x: A)
        cin >> x;

    inizia(N, A);

    for (int i = 0; i < Q; i++) {
        char t;
        cin >> t;

        if (t == 'U') {
            int P, V;
            cin >> P >> V;
            aggiorna(P, V);
        }
        if (t == 'Q') {
            int L, R;
            cin >> L >> R;
            cout << massimo(L, R) << "\n";
        }
    }
}
