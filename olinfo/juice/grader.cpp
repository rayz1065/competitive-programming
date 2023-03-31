#include <iostream>
#include <vector>

using namespace std;

long long harvest(int n, int m, int k, vector<int>& p,
				  vector<int>& v, vector<int>& d, vector<int>& w);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> p(n), v(m), d(m), w(m);
	for (int i = 0; i < n; i++)
		cin >> p[i];
	for (int j = 0; j < m; j++)
		cin >> v[j] >> d[j] >> w[j];
	
	cout << harvest(n, m, k, p, v, d, w) << "\n";
	
	return 0;
}
