#include <bits/stdc++.h>
using namespace std;

void fastIn(int &a){
    a = 0;
    char c = getchar_unlocked();
    while(c < '0')
        c = getchar_unlocked();
    while(c >= '0'){
        a = a*10 + c - '0';
        c = getchar_unlocked();
    }
}

int main(){
    int N, K;
    fastIn(N);
    fastIn(K);

    int C = 0;
    long long M = 0;
    for(int i = 0; i < N; i++){
        int c;
        fastIn(c);

        if(c == 11*K)
            C+= 11;
        else if(c >= 10*K)
            C+= 10, M+= c - 10*K;
        else
            C+= c/K, M+= c - K*(c/K);
    }
    cout<<C<<" "<<M<<"\n";
}