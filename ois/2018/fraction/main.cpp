#include <bits/stdc++.h>

using namespace std;

int periodo(int N){
    int a = 1;
    while((a<<3)+(a<<1) < N)
        a=(a<<3)+(a<<1);
    int iniz = a, c = 0;
    do{
        c++;
        a = ((a<<3)+(a<<1))%N;
    }while(a!=iniz);
    return c;
}

int main(){
    int N, maxP=0;
    cin>>N;
    for(int i=(N-N%2-1); i>maxP; i-=2)
        if(i%5!=0)
            maxP=max(maxP, periodo(i));
    cout<<maxP;
}
