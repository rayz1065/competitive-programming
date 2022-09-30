#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
using namespace std;

vector<vector<int> > grafo;
vector<int> nodi;
vector<bool> usato;
pair<int, int> massimaStrada(int nodo){
    usato[nodo]=true;
    int maxPath1=0, maxPath2=0, maxCicle=0;
    for(int c=0; c<grafo[nodo].size(); c++){
        if(!usato[grafo[nodo][c]]){
            pair<int, int> calcola;
            calcola=massimaStrada(grafo[nodo][c]);
            if(calcola.first>=maxPath1){
                maxPath2=maxPath1;
                maxPath1=calcola.first;
            }
            else if(calcola.first>maxPath2)
                maxPath2=calcola.first;
            if(calcola.second>maxCicle)
                maxCicle=calcola.second;
        }
    }
    //cout<<"nodo "<<nodo<<" max1 = "<<maxPath1<<" max2 = "<<maxPath2<<" maxC = "<<maxCicle<<endl;
    if(maxPath1==0)
        return {1, 0};
    if(maxPath2==0)
        return {maxPath1+1, maxCicle};
    return {maxPath1+1, max(maxPath1+maxPath2+1, maxCicle)};
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    nodi.resize(N);
    grafo.resize(N);
    usato.resize(N, false);
    for(int i=0; i<N; i++){
        int a, b;
        in>>a>>b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    pair<int, int> calcola;
    calcola=massimaStrada(0);
    //cout<<calcola.first<<" "<<calcola.second<<endl;
    out<<max(calcola.first, calcola.second)*2-2;
}
