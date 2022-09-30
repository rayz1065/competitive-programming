#include <bits/stdc++.h>
#define MAXN 9000
#define MAXM 10
using namespace std;

int N, K;
bool model[MAXM][MAXM];
bool painting [MAXN][MAXN];
bool paintingMemo[MAXN][MAXN];

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    in>>N>>K;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++){
            char type;
            in>>type;
            model[i][j]=(type=='.');
            paintingMemo[i][j]=model[i][j];
        }
    int pwN=N;
    for(int c=1; c<K-1; c++, pwN*=N){
        for(int i=0; i<pwN*N; i++){
            for(int b=0; b<N; b++)
                for(int j=0; j<pwN; j++){
                    painting[i][b*pwN+j]=paintingMemo[i%pwN][j]*model[i/pwN][b];

            }
        }
        for(int a=0; a<pwN*N; a++)
            for(int b=0; b<pwN*N; b++)
                paintingMemo[a][b]=painting[a][b];
    }
    for(int i=0; i<pwN*N; i++){
        for(int b=0; b<N; b++)
            for(int j=0; j<pwN; j++){
                out<<((paintingMemo[i%pwN][j]*model[i/pwN][b])?'.':'*');

        }
        out<<endl;
    }
}
