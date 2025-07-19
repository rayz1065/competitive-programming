#include <iostream>
#include <vector>

using namespace std;

vector<int> bilancia(int N, int M, vector<vector<int>> S);

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> S(N);

    for (vector<int>& i : S) {
        int size;
        cin >> size;
        i.resize(size);
        for (int& j : i)
            cin >> j;
    }

    vector<int> ans = bilancia(N, M, S);

    if (ans.size() == 0)
        cout << "IMPOSSIBLE";
    for (int i : ans)
        cout << i << ' ';
    cout << endl;
}
