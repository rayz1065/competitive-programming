#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<long long> calcola(int T, int M, vector<long long> S, vector<long long> P);

int main() {
    ios::sync_with_stdio(false);
    // se preferisci leggere e scrivere da file ti basta decommentare le seguenti due righe:
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int T, M;
    cin >> T >> M;

    vector<long long> S(T), P(M);

    for (long long& x : S) cin >> x;
    for (long long& x : P) cin >> x;

    auto R = calcola(T, M, S, P);

    for (long long x : R) cout << x << ' ';
    cout << endl;

    return 0;
}
