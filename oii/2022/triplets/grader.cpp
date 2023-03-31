#include <cassert>
#include <iostream>
#include <vector>

int build(int N, std::vector<int> A, std::vector<int> B);

int main() {
	// if you want to read from file decomment these two lines
	// assert(freopen("input.txt", "r", stdin));
	// assert(freopen("output.txt", "w", stdout));

	int n;
	assert(std::cin >> n);

	std::vector<int> a(n - 1), b(n - 1);
	for (int i = 0; i < n - 1; ++i) {
		assert(std::cin >> a[i] >> b[i]);
	}

	int ans = build(n, move(a), move(b));
	std::cout << ans << '\n';
}
