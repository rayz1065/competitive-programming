#include <iostream>
#include <vector>
using namespace std;

long long riciclo(int N, int M, vector<int> T, vector<int> P);

int main() {
  int N, M;

  cin >> N >> M;

  vector<int> T(N), P(M);

  for (int i = 0; i < N; i++) {
    cin >> T[i];
  }
  for (int i = 0; i < M; i++) {
    cin >> P[i];
  }

  cout << riciclo(N, M, T, P) << endl;

  return 0;
}
