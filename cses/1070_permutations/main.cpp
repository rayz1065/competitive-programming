#include <bits/stdc++.h>
#define MAXN 500001
using namespace std;

bool found[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin>>N;

    if(N == 2 || N == 3){
        cout<<"NO SOLUTION";
    }
    else{
        for(int i = 2; i <= N; i+= 2)
            cout<<i<<" ";
        for(int i = 1; i <= N; i+= 2)
            cout<<i<<" ";
    }
}
