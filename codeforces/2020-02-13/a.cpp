#include <bits/stdc++.h>

using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        string a, b, c;
        cin >> a >> b >> c;

        bool possible = true;

        for(int i = 0; i < a.length() && possible; i++){
            if(!(a[i] == b[i] && a[i] == c[i])){
                if(a[i] == b[i])
                    possible = false;
                else if(a[i] != c[i] && b[i] != c[i])
                    possible = false;
            }
        }
        cout<<((possible) ? "YES":"NO")<<"\n";
    }
}
