#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
#define MAXN 200
int N, T, login[MAXN], memo[MAXN][MAXN];

int aggiorna(int K, int C){
    if(C==N)
        return 0;
    if(K==1){
        //cout<<"#K==1# allo user "<<C<<" con "<<K<<" aggiornamenti disponibili "<<(T-login[C]+1)*(N-C)<<endl;
        return (T-login[C])*(N-C);
    }
    if(memo[K-1][C]==0){
        int costoMin=1000000;
        for(int j=1; j+C<N; j++)
            costoMin=min(costoMin, aggiorna(K-1, C+j)+j*(T-login[C]));
        memo[K-1][C]=costoMin;
        //cout<<"allo user "<<C<<" con "<<K<<" aggiornamenti disponibili e capienza "<<C<<"  "<<memo[K-1][C]<<endl;
    }
    return memo[K-1][C];
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int K;
    in>>T>>K>>N;
    for(int i=0; i<N; i++)
        in>>login[i];
    /*cout<<"i "<<N<<" user si connetteranno negli istanti:\n";
    for(int i=0; i<N; i++)
        cout<<login[i]<<" ";
    cout<<endl;*/

    out<<aggiorna(K, 0);
}
