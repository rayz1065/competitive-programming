#include <bits/stdc++.h>
#define MAXN 1000000000
using namespace std;

int main(){
    int N=-1;
    set<int> loses;
    for(int i=1; i<=MAXN; i=2*i+1)
        loses.insert(i);
    cin>>N;
    while(N!=0){
        cout<<((loses.find(N)==loses.end())?"Alice":"Bob")<<endl;
        cin>>N;
    }
}
