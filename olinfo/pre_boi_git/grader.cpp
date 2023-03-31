#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void inizia(int N, vector<int> A);
void incrementa(int l, int r, int x);
void resetta(int l, int r, int v);
long long somma(int l, int r);

int main() {
    // comment the following lines if you don't want to read or write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

  	int N, Q;
	cin >> N >> Q;
  
	vector<int> A(N);
  	for (int i = 0; i < N; i++) cin >> A[i];

  	inizia(N, A);

  	for(int i=0; i<Q; i++){
		int op;
		cin >> op;
		if(op == 0){
			int l, r, x; 
			cin >> l >> r >> x;
			incrementa(l, r, x);
		}

		if(op == 1){
			int l, r, v; 
			cin >> l >> r >> v;
			resetta(l, r, v);
		}

		if(op == 2){
			int l, r; 
			cin >> l >> r;
			cout << somma(l, r) << endl;
		}
	}
}
