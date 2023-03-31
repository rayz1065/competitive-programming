#include <iostream>
#include <vector>

using namespace std;

long long smaltisci(int N, int M, vector<int> A, vector<vector<int>> B);

int main() {
  int N, M;

  cin >> N >> M;

  vector<int> A(M), K(M);
  vector<vector<int>> B(M);

  for (int i = 0; i < M; i++) {
    cin >> A[i] >> K[i];

    B[i].resize(K[i]);
    for (int j = 0; j < K[i]; j++) {
      cin >> B[i][j];
    }
  }

  cout << smaltisci(N, M, A, B) << "\n";
}
