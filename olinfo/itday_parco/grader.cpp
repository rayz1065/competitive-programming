#include <iostream>
#include <vector>

using namespace std;

long long visita(int N, int X, int T, vector<int> K, vector<vector<int>> W, vector<vector<int>> F);

int main() {
    int N, X, T;
    cin >> N >> X >> T;

    vector<int> K(N);
    vector<vector<int>> W(N);
    vector<vector<int>> F(N);

    for (int i = 0; i < N; i++) {
        cin >> K[i];
        W[i].resize(K[i]);
        F[i].resize(K[i]);
        for (int j = 0; j < K[i]; j++) {
            cin >> W[i][j] >> F[i][j];
        }
    }

    cout << visita(N, X, T, K, W, F) << endl;

    return 0;
}
