#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int taglia(int N, vector<int> B);

int main() {
  // Uncomment the following lines if you want to read or write from files
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> B(N);
  for (int i = 0; i < N; i++) cin >> B[i];

  cout << taglia(N, B) << endl;

  return 0;
}
