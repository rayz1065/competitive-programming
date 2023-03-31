#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int presta(int N, int C, vector<int> P);

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int N, C;
  assert(cin >> N);
  assert(cin >> C);

  vector<int> P(N);
  for (int& p : P) {
    assert(cin >> p);
  }
  cout << presta(N, C, move(P)) << "\n";
}
