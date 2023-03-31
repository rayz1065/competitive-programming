#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int direziona(int N, vector<int> A, vector<int> B);

int main() 
{
	int N;
	cin >> N;

	vector<int> A(N), B(N);
	for (int& x : A) cin >> x;
	for (int& x : B) cin >> x;

	cout << direziona(N, A, B) << "\n";

	return 0;
}
