#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define MAXN 10000
#define MAXM 100000
using namespace std;

struct info{
    int arrivo;
    int catena;
    int vel;
};
vector<int> grafo[MAXN];
info strade[MAXM];

int percorri(int nodo, int vel){
    int maxD=0;
    for(int i=0; i<grafo[nodo].size(); i++){
        if(strade[grafo[nodo][i]].vel>vel){
            if(strade[grafo[nodo][i]].catena==-1)
                strade[grafo[nodo][i]].catena=percorri(strade[grafo[nodo][i]].arrivo, strade[grafo[nodo][i]].vel)+1;
            maxD=max(maxD, strade[grafo[nodo][i]].catena);
        }
    }
    return maxD;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    int N, M;
    in>>N>>M;

    for(int i=0; i<M; i++){
        int da, a, vel;
        in>>da>>a>>vel;
        grafo[da].push_back(i);
        strade[i]=(info){a, -1, vel};
    }

    int maxStrada=1;
    for(int i=0; i<N; i++)
        maxStrada=max(percorri(i, 0), maxStrada);
    out<<maxStrada;
}
