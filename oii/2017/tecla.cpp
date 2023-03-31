#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 31
vector<int> tela[MAXN];
pair<int, int> nodes[MAXN]; //first se non ha appetito, second se ha appetito
vector<int> percorso;

void percorri(){
    queue<pair<int, bool> > FF;
    FF.push({0, false});
    nodes[0].first=0;
    while(!FF.empty()){
        int nodo=FF.front().first;
        bool slurp=FF.front().second;
        FF.pop();
        if(slurp){
            for(int i=0; i<tela[nodo].size(); i++){
                if(nodes[tela[nodo][i]].first==1000000){
                    nodes[tela[nodo][i]].first=nodes[nodo].second+1;
                    FF.push({tela[nodo][i], !slurp});
                }
            }
        }
        else{
            for(int i=0; i<tela[nodo].size(); i++){
                if(nodes[tela[nodo][i]].second==1000000){
                    nodes[tela[nodo][i]].second=nodes[nodo].first+1;
                    FF.push({tela[nodo][i], !slurp});
                }
            }
        }
    }
}

void stampa(int nodo, bool slurp){
    percorso.push_back(nodo);
    if(nodo==0&&!slurp)
        return;
    if(slurp){
        for(int i=0; i<tela[nodo].size(); i++){
            if(nodes[nodo].second==nodes[tela[nodo][i]].first+1){
                stampa(tela[nodo][i], !slurp);
                return;
            }
        }
    }
    else{
        for(int i=0; i<tela[nodo].size(); i++){
            if(nodes[nodo].first==nodes[tela[nodo][i]].second+1){
                stampa(tela[nodo][i], !slurp);
                return;
            }
        }
    }
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, M;
    in>>N>>M;
    for(int i=0; i<M; i++){
        int u, v;
        in>>u>>v;
        tela[u].push_back(v);
        tela[v].push_back(u);
    }
    for(int i=0; i<N; i++){
        nodes[i].first=1000000;
        nodes[i].second=1000000;
    }
    percorri();
    stampa(0, true);
    out<<nodes[0].second<<endl;
    for(int i=0; i<percorso.size(); i++)
        out<<percorso[i]<<" ";
}
