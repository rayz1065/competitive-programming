#include <bits/stdc++.h>

using namespace std;

string acidNaming(string S) {
    if(S[S.size()-2] == 'i' && S[S.size()-1] == 'c'){
        if(S.substr(0, 5) == "hydro")
            return "non-metal acid";
        return "polyatomic acid";
    }
    return "not an acid";
}

int main() {
    int n;
    cin >> n;
    for(int a0 = 0; a0 < n; a0++){
        string acid_name;
        cin >> acid_name;
        string result = acidNaming(acid_name);
        cout << result << endl;
    }
    return 0;
}
