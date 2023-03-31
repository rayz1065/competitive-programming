#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int organizza(int N, int X, int Y, vector<int> A, vector<int> B);

int main() {
  // Uncomment the following lines if you want to read or write from files
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int N, X, Y;
  cin >> N >> X >> Y;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i];
  }

  cout << organizza(N, X, Y, A, B) << endl;

  return 0;
}
