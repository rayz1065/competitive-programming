#include <iostream>

using namespace std;

int compila(int D, int X, int N, int S) {
    int free = D - S * N;
    int exceeding = X - free;
    return max(0, exceeding / S + (exceeding % S > 0));
}
