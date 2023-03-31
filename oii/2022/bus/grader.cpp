#include <iostream>
#include <vector>

using namespace std;

int pianifica(int N, int L, vector<vector<int>> F);

int main() {
    ios_base::sync_with_stdio(false);
    // se preferisci leggere e scrivere da file ti basta decommentare le seguenti due righe:
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int N, L;
    cin >> N >> L;

    vector<vector<int>> F(L);
    for (int i = 0; i < L; i++) {
        int K;
        cin >> K;
        F[i].resize(K);
        for (int j = 0; j < K; j++) {
            cin >> F[i][j];
        }
    }

    cout << pianifica(N, L, F) << endl;

    return 0;
}
