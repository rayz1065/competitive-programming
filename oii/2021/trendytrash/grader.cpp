#include <iostream>
#include <vector>
#include <string>
using namespace std;

int pulisci(int N, int M, vector<string> S);

int main() {
  int N, M;

  cin >> N >> M;

  vector<string> S(N);

  for(int i = 0; i < N; i++) {
    cin >> S[i];
  }

  cout << pulisci(N, M, S) << endl;

  return 0;
}
