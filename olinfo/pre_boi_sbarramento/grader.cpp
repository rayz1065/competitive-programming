#include <fstream>
#include <iostream>
#include <vector>
#include <ios>


using namespace std;

long long fuggi(int N, int M, vector <int> A, vector <int> B, vector <int> T, vector <int> R);

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // Uncomment the following lines if you want to read or write from files
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int N, M;
  cin >> N >> M;

  vector <int> A(M), B(M), T(M);
  vector <int> R(M, 0);
  for (int i = 0; i < M; i++) {
    cin >> A[i] >> B[i] >> T[i] >> R[i];
  }

  cout << fuggi(N, M, A, B, T, R);

  return 0;
}
