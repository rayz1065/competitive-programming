#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int gioca(int N, int K, vector<vector<int>> M);

int main() {
    int N; cin >> N;
    int K; cin >> K;

    vector<vector<int>> M(N, vector<int> (K));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            cin >> M[i][j];
        }
    }

    cout << gioca(N, K, M) << endl;

    return 0;
}
