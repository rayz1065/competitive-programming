#include <bits/stdc++.h>

using namespace std;

int main(){
    int N, val, zeri;
    cin>>N;
    for(int x=1; N!=0; x++){
        zeri=0;
        for(int i=0; i<N; i++){
            cin>>val;
            if(val==0)
                zeri++;
        }
        cout<<"Case "<<x<<": "<<N-2*zeri<<endl;
        cin>>N;
    }
}
