#include<bits/stdc++.h>

using namespace std;

int visita(int N, vector<int> &A, vector<int> &B, vector<int> &dolcezza, vector<int> &C);

int main(){
	int N;
	cin >> N;
	vector<int> dolcezza(N), C(N), A(N - 1), B(N - 1);
	for (int i = 0; i < N; i++) {
		cin >> dolcezza[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> C[i];
	}
	for (int i = 0; i < N - 1; i++) {
		cin >> A[i] >> B[i];
	}
	cout << visita(N, A, B, dolcezza, C) << endl;
	return 0;
}
