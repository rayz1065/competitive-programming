#include <bits/stdc++.h>
#define MAXN 31
using namespace std;
typedef pair<int, int> pii;

int N, K;
int crediti[MAXN];
int S = INT_MAX;
vector<pii> grafo[MAXN];
bool usato[MAXN];

void esplora(int nodo, int costo, int c){
    //cout<<nodo<<", costo = "<<costo<<", crediti = "<<c<<endl;
    if(costo >= S)
        return;
    if(c >= K){
        S = min(S, costo);
        return;
    }
    for(auto i:grafo[nodo]){
        if(!usato[i.first]){
            usato[i.first] = true;
            esplora(i.first, costo + i.second, c + crediti[i.first]);
            usato[i.first] = false;
        }
    }
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in>>K>>N;

    for(int i = 0; i < N; i++)
        in>>crediti[i];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int ore;
            in>>ore;
            if(ore > 0)
            grafo[i].push_back({j, ore});
        }
    }

    for(int i = 0; i < N; i++){
        usato[i] = true;
        esplora(i, 0, crediti[i]);
        usato[i] = false;
    }
    out<<S;
}
