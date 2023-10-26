#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool ordina(int N, vector<int> V, vector<int> &L);

int main() {
    int N;
    cin >> N;
  
    vector<int> V(N);
    for (int i = 0; i < N; ++i) {
        cin >> V[i];
    }

    vector<int> L;
    bool risposta = ordina(N, V, L);

    if (risposta == true) {
        cout << "YES" << endl;

        int M = L.size();
        cout << M << endl;

        for (int i = 0; i < M; ++i) {
            cout << L[i] << " ";
        }
        cout << endl;

    } else {
        cout << "NO" << endl;
    }
}
