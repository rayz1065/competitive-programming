#include <iostream>
#include <vector>
using namespace std;

int conta(int N, vector<int> D);

int main() {
	// if you want to read from file decomment these two lines
	// assert(freopen("input.txt", "r", stdin));
	// assert(freopen("output.txt", "w", stdout));

	int n;
	cin >> n;

	vector<int> d(n);
	for (auto &x : d)
		cin >> x;

	int ans = conta(n, d);
	cout << ans << '\n';
}
