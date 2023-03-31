#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> trovacerchi(int N, std::vector<int> X, std::vector<int> Y);

int main() {

	// decommenta le seguenti righe per leggere e/o scrivere su file:
	// std::ifstream cin("input.txt");
	// std::ofstream cout("output.txt");

	int N;
	std::cin >> N;
	std::vector<int> X(N), Y(N);
	for (int i = 0; i < N; i++) {
		std::cin >> X[i] >> Y[i];
	}

	// -------
	
	std::vector<int> risultato = trovacerchi(N, X, Y);

	// -------

	for (int i: risultato) {
		std::cout << i << " ";
	}
	std::cout << "\n";

	return 0;
}
