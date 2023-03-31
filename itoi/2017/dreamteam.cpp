#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, K;
    in>>N>>K;
    int brav[2*N];
    fill(brav, brav+2*N, -1000000000);
    for(int i=0; i<N; i++){
        int F, P, Q;
        in>>F>>P>>Q;
        if(F>i){
            brav[2*i]=P;
            brav[2*i+1]=Q;
        }
        else{
            brav[2*F]=max(brav[2*F], P);
            brav[2*F+1]=brav[2*F+1]+Q-brav[2*F];
        }
    }
    sort(brav, brav+2*N);
    int S=0;
    for(int i=2*N-1; i>=2*N-K; i--)
        S+=brav[i];
    out<<S;
}
