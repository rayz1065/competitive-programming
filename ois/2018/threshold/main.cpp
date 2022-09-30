#include <bits/stdc++.h>
#define MAXN 101
using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    int ammessi[MAXN]={};

    for(int i=0; i<N; i++){
        int voto;
        in>>voto;
        ammessi[voto]++;
    }

    int S = 0;
    for(int i=100; i>=0; i--){
        S+= ammessi[i];
        out<<S<<" ";
    }
}
