#include <bits/stdc++.h>
#define MAXN 55

using namespace std;

set<string> found;

int main() {
    string curr;
    bool no_space = true;
    while(cin >> curr) {
        string key;
        for(int i = 0; i < curr.length(); i++) {
            key.push_back(tolower(curr[i]));
        }
        char sep = getchar();
        if(found.find(key) == found.end()) {
            cout << curr;
            found.insert(key);
        }
        else {
            cout << '.';
        }
        cout << sep;
    }
}