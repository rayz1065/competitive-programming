#include <iostream>
#include <vector>

using namespace std;

int visita(int N, int M, int K, vector<int> S, vector<int> A, vector<int> B, vector<int> T);

int main() {
    int N, M, K; cin >> N >> M >> K;
    vector<int> S(K), A(M), B(M), T(M);

    for(int i=0; i<K; i++){
        cin >> S[i];
    }

    for(int i=0; i<M; i++){
        cin >> A[i] >> B[i] >> T[i];
    }

    cout << visita(N, M, K, S, A, B, T) << "\n";
}
