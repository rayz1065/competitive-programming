#include <iostream>
#include <string>
using namespace std;

int affetta(int N, int K, string S);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); 

    int N, K;
    cin >> N >> K;

    string S;
    cin >> S;

    cout << affetta(N, K, S) << endl;
}
