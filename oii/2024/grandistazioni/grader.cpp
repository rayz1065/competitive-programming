#include <iostream>
#include <vector>
#include <utility>
using namespace std;

long long viaggia(int N, int M, vector<int> A, vector<int> B, vector<int> T, vector<int> V, vector<int> W);

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> A(M), B(M), T(M), V(N), W(N);
    for (int i = 0; i < N; i++)
        cin >> V[i];
    for (int i = 0; i < N; i++)
        cin >> W[i];
    
    for (int i = 0; i < M; i++)
        cin >> A[i] >> B[i] >> T[i];
    
    cout << viaggia(N, M, A, B, T, V, W) << '\n';
}
