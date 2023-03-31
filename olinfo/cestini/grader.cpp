#include <iostream>
#include <fstream>
using namespace std;

// Declaring functions
void inizia(int N, int M);
void sposta(int a, int b);
int controlla(int a, int i);

int main() {
    // Uncomment the following lines if you want to read/write from files
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");

    ios::sync_with_stdio(false);

    int N, M, Q;
    cin >> N >> M >> Q;

    inizia(N, M);

    for (int i = 0; i < Q; i++) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        if (t == 's') {
            sposta(a, b);
        } else {
            cout << controlla(a, b) << '\n';
        }
    }

    return 0;
}
