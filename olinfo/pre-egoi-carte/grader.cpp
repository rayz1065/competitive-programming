#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int scarta(int C, vector<bool> L, vector<bool> D, vector<bool> N);

int main() {
  // Uncomment the following lines if you want to read or write from files
  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  int C;
  cin >> C;

  vector<bool> L(C, false), D(C, false), N(C, false);
  for (int i = 0; i < C; i++) {
    int l, d, n;
    cin >> l >> d >> n;
    if (l) L[i] = true;
    if (d) D[i] = true;
    if (n) N[i] = true;
  }

  cout << scarta(C, L, D, N);

  return 0;
}
