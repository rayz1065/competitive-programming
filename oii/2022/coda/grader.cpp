#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<int> cucina(int N, int K, int X, vector<int> H);

int main() {
    // se preferisci leggere e scrivere da file ti basta decommentare le seguenti due righe:
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int N, K, X;
    cin >> N >> K >> X;

    vector<int> H(N);
    for (int& h : H) {
        cin >> h;
    }

    vector<int> res = cucina(N, K, X, move(H));
    for (int r : res) {
        cout << r << ' ';
    }
    cout << endl;

    return 0;
}
