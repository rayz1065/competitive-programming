#include <bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin >> T;

    for(int t = 0; t < T; t++){
        long long x, y;
        cin >> x >> y;

        if(abs(x-y) == 1)
            cout<<"NO\n";
        else
            cout<<"YES\n";
    }
}
