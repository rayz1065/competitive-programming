#include <iostream>
#include <vector>
using namespace std;

void mincammino(int N, int M, vector<int> X, vector<int> Y, vector<int> P, vector<long long>& D);

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> X(M), Y(M), P(M);
    vector<long long> D(N);

    for (int i = 0; i < M; i++) {
        cin >> X[i] >> Y[i] >> P[i];
    }

    mincammino(N, M, X, Y, P, D);

    for (int i = 0; i < N; i++) {
        cout << D[i] << ' ';
    }
    cout << '\n';
}
