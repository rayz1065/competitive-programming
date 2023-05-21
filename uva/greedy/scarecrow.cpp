#include <bits/stdc++.h>

using namespace std;

int main(){
    int T, N;
    cin>>T;
    for(int i=0; i<T; i++){
        cin>>N;
        char campo[N];
        cin>>campo;
        int S=0;
        for(int j=0; j<N; j++){
            if(campo[j]=='.')
                S++, j+=2;
        }
        cout<<"Case "<<i+1<<": "<<S<<endl;
    }
}
