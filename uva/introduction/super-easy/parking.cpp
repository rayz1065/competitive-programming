#include <bits/stdc++.h>

using namespace std;

int main(){
    int T, N, val;
    cin>>T;
    for(int a=0; a<T; a++){
        cin>>N;
        int mini=101, massi=-1;
        for(int i=0; i<N; i++){
            cin>>val;
            massi=max(massi, val);
            mini=min(mini, val);
        }
        cout<<(massi-mini)*2<<endl;
    }
}
