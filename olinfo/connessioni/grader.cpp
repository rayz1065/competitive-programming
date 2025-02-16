#include <iostream>
using namespace std;

void inizia(int N);
int collega(int X, int Y);

int main() {
    int N, Q;
    cin >> N >> Q;

    inizia(N);

    for (int i = 0; i < Q; i++) {
        int X, Y; 
        cin >> X >> Y;
        cout << collega(X, Y) << "\n";
    }
}
