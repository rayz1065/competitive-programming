#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int K, N, M;
    in>>K>>N>>M;
    vector<vector<pair<int,int> > > grafo(N);
    for(int i=0; i<M; i++){
        int a,b,miglia;
        in>>a>>b>>miglia;
        grafo[a].push_back({b,miglia});
    }
    queue<pair<int,int> > FF;
    set<int> inserisci;
    int pos, dist, maxm(0);
    vector<pair<int,int> > citta(N,{0,0});
    FF.push({0,0});
    for(int c=0; c<K; c++){
        while(!FF.empty()){
            pos=FF.front().first;
            dist=FF.front().second;
            FF.pop();
            for(int i=0; i<grafo[pos].size(); i++){
                if(citta[grafo[pos][i].first].first!=c||grafo[pos][i].second+dist>citta[grafo[pos][i].first].second){
                    inserisci.insert(grafo[pos][i].first);
                    citta[grafo[pos][i].first].second=dist+grafo[pos][i].second;
                    citta[grafo[pos][i].first].first=c;
                    if(c==K-1&&dist+grafo[pos][i].second>maxm&&grafo[pos][i].first==0)
                        maxm=dist+grafo[pos][i].second;
                }
            }
        }
        while(!inserisci.empty()){
            FF.push({*inserisci.begin(),citta[*inserisci.begin()].second});
            inserisci.erase(inserisci.begin());
        }
    }
    out<<maxm;
}
