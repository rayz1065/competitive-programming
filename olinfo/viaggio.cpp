#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <climits>

std::set<std::pair<int,int> > FF;
std::vector<std::vector<std::pair<int,int> > > grafo;
std::vector<int> citta;
using namespace std;
int vola(int n){
    int pos;
    while(!FF.empty()&&FF.begin()->first<citta[n]){
        pos=FF.begin()->second;
        FF.erase(FF.begin());
        for(int i=0; i<grafo[pos].size(); i++){
            if(citta[pos]+grafo[pos][i].second<citta[grafo[pos][i].first]){
                int target=grafo[pos][i].first;
                citta[target]=citta[pos]+grafo[pos][i].second;
                FF.insert({citta[pos]+grafo[pos][i].second,target});
            }
        }
    }
    return citta[n];
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n,m;
    in>>n>>m;
    citta.resize(n+1,INT_MAX);
    grafo.resize(n+1);
    for(int i=0; i<m; i++){
        int a, b, costo;
        in>>a>>b>>costo;
        grafo[a].push_back({b,costo});
        grafo[b].push_back({a,costo});
    }
    citta[1]=0;
    FF.insert({0,1});
    out<<vola(n);
}
