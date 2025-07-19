#include <iostream>
#include <vector>

using namespace std;

int traffico(int N, vector<int> S);

int main() {
    int N; cin >> N;

    vector<int> S(N);

    for (auto &s: S) {
        cin >> s;
    }

    cout << traffico(N, S) << endl;
}
