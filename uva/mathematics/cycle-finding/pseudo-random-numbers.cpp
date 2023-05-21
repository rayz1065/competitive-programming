#include <bits/stdc++.h>
#define MAXN 10000
using namespace std;

int found[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int c = 0;
    int Z, I, M, L;
    cin>>Z>>I>>M>>L;
    while(!(Z==0 && I==0 && M==0 && L==0)){
        for(int i = 0; i < MAXN; i++)
            found[i] = -1;
        //cout<<endl;
        //cout<<L<<" -> "<<found[L]<<endl;
        int i = 0;
        for(; found[L] == -1; i++){
            found[L] = i;
            L = (Z * L + I)%M;
            //cout<<L<<" -> "<<found[L]<<endl;
        }
        cout<<"Case "<<++c<<": "<<i - found[L]<<endl;
        cin>>Z>>I>>M>>L;
    }
}
