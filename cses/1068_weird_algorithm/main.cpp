#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    long long N;
    cin>>N;

    while(N != 1){
        cout<<N<<" ";
        if(N%2 == 0)
            N = N>>1;
        else
            N = (N<<1) + N + 1;
    }
    cout<<N;
}
