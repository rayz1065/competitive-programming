#include <iostream>

using namespace std;

int compila(int D, int X, int N, int S);

int main() {

    int D, X, N, S;
    cin >> D >> X >> N >> S;

    cout << compila(D, X, N, S) << endl;
}
