#include <bits/stdc++.h>

using namespace std;

int main(){
    int N;
    cin>>N;
    for(int i=0; i<N; i++){
        int a, b;
        cin>>a>>b;
        cout<<((a>b)?'>':(a<b)?'<':'=')<<endl;
    }
}
