#include <vector>
#include <iostream>

using namespace std;

void init(int n);
void log(vector<int>& added, vector<int>& removed);
int answer(int d, int x);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	init(n);
	
	vector<int> added, removed;
	for (int i = 1; i <= n; i++) {
		added.clear();
		int a;
		cin >> a;
		for (int j = 0; j < a; j++) {
			int k;
			cin >> k;
			added.push_back(k);
		}
		removed.clear();
		int r;
		cin >> r;
		for (int j = 0; j < r; j++) {
			int k;
			cin >> k;
			removed.push_back(k);
		}
		log(added, removed);
	}
	
	for (int i = 0; i < q; i++) {
		int d, x;
		cin >> d >> x;
		cout << answer(d, x) << "\n";
	}
	
	return 0;
}
