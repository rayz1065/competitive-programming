#include <bits/stdc++.h>
#define MAXT 10005
#ifdef _WIN32
    #define getchar_unlocked getchar
#endif // _WIN32
using namespace std;

void readNum(int &N){
    char c = getchar_unlocked();
    N = 0;
    while(c > '/'){
        N = (N * 10) + c - '0';
        c = getchar_unlocked();
    }
}

int N, M, T;
int altezze[MAXT];
int altDue[MAXT*2];

int main(){
    readNum(N);
    readNum(M);
    readNum(T);

    for(int i = 0; i < N; i++){
        int h;
        readNum(h);
        altezze[h]++;
    }
    altezze[0] = N;
    for(int i = 0; i < MAXT; i++)
        altDue[2*i]+= altezze[i]/2;
    for(int i = 0; i < MAXT; i++){
        for(int j = i + 1; j < MAXT; j++){
            altDue[i + j]+= min(altezze[i], altezze[j]);
        }
    }

    for(int i = T; i < MAXT*2; i++){
        if(altDue[i] >= M){
            cout<<i<<"\n";
            return 0;
        }
    }
    cout<<"IMPOSSIBLE\n";
}
