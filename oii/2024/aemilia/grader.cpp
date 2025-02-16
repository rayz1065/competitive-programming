#include <iostream>
#include <vector>
using namespace std;

vector<int> verifica(int N, vector<int> T);

int main() {
    int N;
    cin >> N;

    vector<int> T(N);
    for (int i = 0; i < N; i++)
        cin >> T[i];

    vector<int> P = verifica(N, T);
    
    cout << P.size() << '\n';
    for (int i = 0; i < P.size(); i++)
        cout << P[i] << ' ';
    cout << '\n';
}
