#include <iostream>
#include <fstream>
#define MAXN 100
#define MAXL 1001
#define modulo 10007
using namespace std;

int N, K, L, Kfatt;
int tomb[MAXN];
int somme[MAXN+1];
int memo[MAXN][MAXN][MAXL]; //i, tombini scelti*MAXN, L rimanenti*MAXN^2

int fatt(int N){
    if(N<=1)
        return 1;
    return (N*fatt(N-1))%modulo;
}

int assorbi(int i, int C, int La){
    if(K-C==0)
        return (La==L)? 1:0;

    if(K-C==N-i)
        return (La+somme[N]-somme[i]>=L)? 1:0;

    if(memo[i][C][La]==0)
        memo[i][C][La]=assorbi(i+1, C, La)+assorbi(i+1, C+1, min(L, La+tomb[i]))+1;
    return memo[i][C][La]%modulo-1;
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    in>>L>>N>>K;
    N--;

    Kfatt=(fatt(K)*fatt(N-K))%modulo;
    somme[0]=0;
    for(int i=0; i<N; i++){
        in>>tomb[i];
        somme[i+1]=somme[i]+tomb[i];
    }
    out<<(assorbi(0, 0, 0)*Kfatt)%modulo;
}
