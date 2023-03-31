#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

using namespace std;
int main(){
    vector<vector<pair<int, int> > > grafo;
    set<pair<unsigned long long int, int> > FF;
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int n, m, inizio, fine;
    cin>>n>>m>>inizio>>fine;
    vector<unsigned long long int> nodi(n+1, ULLONG_MAX);
    grafo.resize(n+1);
    for(int i=0; i<m; i++){
        int sorg, dest, arco;
        cin>>sorg>>dest>>arco;
        grafo[sorg].push_back({dest, arco});
        grafo[dest].push_back({sorg, arco});
    }
    FF.insert({0,inizio});
    nodi[inizio]=0;
    int curr;
    while(!FF.empty()){
        curr=FF.begin()->second;
        FF.erase(FF.begin());
        for(int i=0; i<grafo[curr].size(); i++){
            if(nodi[curr]+grafo[curr][i].second<nodi[grafo[curr][i].first]){
                int p=grafo[curr][i].first;
                FF.erase({nodi[p],p});
                nodi[p]=nodi[curr]+grafo[curr][i].second;
                FF.insert({nodi[p],p});
            }
        }
    }
    cout<<nodi[fine];
}
