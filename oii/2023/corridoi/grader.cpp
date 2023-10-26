#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

vector<long long> shorten(int N, int M, int Q, vector<long long> K, vector<int> A, vector<int> B, vector<int> C);

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<long long> K(Q);
    for (int i = 0; i < Q; i++) {
        cin >> K[i];
    }
    vector<int> A(M), B(M), C(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> C[i];
    }

    vector<long long> soluzione = shorten(N, M, Q, K, A, B, C);
    cout << soluzione.size() << "\n";
    for (int i = 0; i < soluzione.size(); i++) {
        cout << soluzione[i] << ' ';
    }
    cout << "\n";
}
