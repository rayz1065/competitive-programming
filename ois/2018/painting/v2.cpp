#include <bits/stdc++.h>
#define MAXN 8500
#define MAXM 11
using namespace std;

int N, K;
bool painting[MAXN][MAXN];
bool model[MAXM][MAXM];
int power[MAXM];

void generatePainting(int k, int i1, int j1){
    if(k==1){
        for(int i = 0; i<N; i++)
            for(int j = 0; j<N; j++)
                painting[i+i1][j+j1] = model[i][j];
        return;
    }
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(model[i][j])
                generatePainting(k-1, i1+power[k-1]*i, j1+power[k-1]*j);
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in>>N>>K;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++){
            char type;
            in>>type;
            model[i][j] = (type=='.');
        }
    power[0]=1;
    for(int i=1; i<MAXM; i++)
        power[i] = power[i-1]*N;

    generatePainting(K, 0, 0);

    for(int i=0; i<power[K]; i++){
        for(int j=0; j<power[K]; j++)
            out<<(painting[i][j]?'.':'*');
        out<<endl;
    }
}
