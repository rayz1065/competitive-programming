#include <bits/stdc++.h>

using namespace std;

int main () {
    int n;
    cin >> n;
    stack<int> animals;
    for (int i = 0; i < n; i++) {
        int sz;
        cin >> sz;
        while (!animals.empty() && sz > animals.top()) animals.pop();
        animals.push(sz);
    }
    cout << animals.size() << "\n";
}
