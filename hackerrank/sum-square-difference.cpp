#include <bits/stdc++.h>

using namespace std;

long long calcola(int N){
    long long a = 0, b = 0;
    for(int i=1; i<=N; i++){
        a+= i;
        b+= i*i;
    }
    return a*a-b;
}

int main(){
    int T;
    cin>>T;
    for(int i=0; i<T; i++){
        int N;
        cin>>N;
        cout<<calcola(N)<<endl;
    }
}
