#include <utility>
#include <iostream>
#include <vector>
using namespace std;

// Declaring variables
static int R;
static vector<int> risultato1;
static vector<int> risultato2;

// Declaring functions
void inizializza(int N, vector<int> H);

// Functions ad-hoc for this grader
pair<int, int> chiedi(int x);
void cambia(int x, int h);

void leggi_eventi(int M) {
    for (int i = 0; i < M; i++) {
        char tipo;
        cin >> tipo;

        if (tipo == 'Q') {
            int x;
            cin >> x;
            pair<int, int> risultato = chiedi(x);
            risultato1[R] = risultato.first;
            risultato2[R] = risultato.second;
            R++;
        } else {
            int x, h;
            cin >> x >> h;
            cambia(x, h);
        }
    }
}


int main() {
	// Reading input
	int N, M;
	cin >> N >> M;

	vector<int> H(N);
	risultato1.resize(M);
	risultato2.resize(M);

	for (int i = 0; i < N; i++) {
		cin >> H[i];
	}
	
	// Calling functions
	inizializza(N, H);
	leggi_eventi(M);

	// Writing output
	for (int i = 0; i < R; i++) {
		cout << risultato1[i] << ' ' << risultato2[i] << '\n';
	}

	return 0;
}
