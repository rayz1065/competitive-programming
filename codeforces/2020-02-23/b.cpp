#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int costo[MAXN];

int get_costo(char c, int a, int b){
    if(c == 'A') return a;
    return b;
}

int solve(int p, int n){
    for(int i = n - 1; i >= 0; i--){
        if(costo[i] > p) return i + 1;
    }
    return 0;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        int a, b, p, n;
        string s;
        cin >> a >> b >> p >> s;
        n = s.length();
        s.pop_back();
        s.push_back('$');

        costo[n - 1] = 0;
        for(int i = n - 2; i >= 0; i--){
            if(s[i] == s[i + 1]) costo[i] = costo[i + 1];
            else                 costo[i] = costo[i + 1] + get_costo(s[i], a, b);
        }

        //for(int i = 0; i <= n; i++)
        //    cout<<i<<": "<<costo[i]<<"\n";

        cout<<solve(p, n) + 1<<"\n";
    }
}
