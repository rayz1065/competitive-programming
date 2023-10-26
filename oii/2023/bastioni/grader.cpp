#include <iostream>
#include <cassert>
using namespace std;

int arrampicate(int N, string S);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); // Remove these two lines in interactive problems.

    int N;
    assert(cin >> N);
    
    string S;
    assert(cin >> S);

    cout << arrampicate(N, move(S)) << '\n';

}
