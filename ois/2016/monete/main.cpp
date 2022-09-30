#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

std::queue<int> FF;
std::vector<std::pair<int,bool> > nodi;
std::vector<std::vector<int> > grafo;
int raccogli(int n){
    int somma=nodi[0].first, pos;
    FF.push(0);
    nodi[0].second=true;
    while(!FF.empty()){
        pos=FF.front();
        FF.pop();
        for(int i=0; i<grafo[pos].size(); i++){
            if(!nodi[grafo[pos][i]].second){
                somma+=nodi[grafo[pos][i]].first;
                nodi[grafo[pos][i]].second=true;
                FF.push(grafo[pos][i]);
            }
        }
    }
    return somma;
}


int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n,m;
    in>>n>>m;
    grafo.resize(n);
    nodi.resize(n);
    for(int i=0; i<n; i++){
        int monete;
        in>>monete;
        nodi[i]={monete, 0};
    }
    for(int i=0; i<m; i++){
        int partenza, arrivo;
        in>>partenza>>arrivo;
        grafo[partenza].push_back(arrivo);
        grafo[arrivo].push_back(partenza);
    }
    out<<raccogli(n);
}
