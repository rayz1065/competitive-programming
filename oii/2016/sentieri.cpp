#include <iostream>
#include <cstdio>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

std::set<std::pair<int,int> > FF;
std::vector<std::vector<std::pair<int,int> > > grafo; //primo: direzione, secondo: peso
std::vector<int> incroci;

int scappa(int n){
    int pos;
    while(!FF.empty()){
        pos=FF.begin()->second;
        FF.erase(FF.begin());
        for(int i=0; i<grafo[pos].size(); i++){
            if(incroci[pos]+grafo[pos][i].second<incroci[grafo[pos][i].first]){
                FF.insert({incroci[pos]+grafo[pos][i].second,grafo[pos][i].first});
                incroci[grafo[pos][i].first]=incroci[pos]+grafo[pos][i].second;
            }
        }
    }
    return(incroci[n]);
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n, a, b;
    in>>n>>a>>b;
    incroci.resize(n+1,1000);
    grafo.resize(n+1);
    for(int i=0; i<a; i++){
        int partenza, arrivo;
        in>>partenza>>arrivo;
        grafo[partenza].push_back({arrivo,0});
        grafo[arrivo].push_back({partenza,0});
    }
    for(int i=0; i<b; i++){
        int partenza, arrivo;
        in>>partenza>>arrivo;
        grafo[partenza].push_back({arrivo,1});
        grafo[arrivo].push_back({partenza,1});
    }
    incroci[1]=0;
    FF.insert({0,1});
    out<<scappa(n);
}