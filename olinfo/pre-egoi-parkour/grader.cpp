#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int salta(int N, vector<int> S, vector<int> A, vector<int> B);

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  // Uncomment the following lines if you want to read or write from files
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int N;
  cin >> N;

  vector<int> S(N), A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> S[i] >> A[i] >> B[i];
  }

  cout << salta(N, S, A, B) << endl;

  return 0;
}
