#include <bits/stdc++.h>
#define MAXN 50005
using namespace std;

int S[MAXN];
int padre[MAXN];
int nodeRank[MAXN];
vector<pair<int, int> > archi[MAXN];

int risali(int nodo){
    if(padre[nodo] != nodo)
        padre[nodo] = risali(padre[nodo]);
    return padre[nodo];
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N, K, T;
    in>>N>>K>>T;

    for(int i = 0; i<K; i++){
        int da, a, peso;
        in>>da>>a>>peso;
        archi[peso].push_back({da, a});
    }

    for(int i=0; i<MAXN; i++){
        padre[i] = i;
        nodeRank[i] = 0;
    }
    int cluster = N;
    for(int peso = 50000; peso > 0; peso--){
        for(auto arco:archi[peso]){
            if(risali(arco.first) != risali(arco.second)){
                if(nodeRank[padre[arco.first]] > nodeRank[padre[arco.second]])
                    padre[padre[arco.second]] = padre[arco.first];
                else if(nodeRank[padre[arco.first]] < nodeRank[padre[arco.second]])
                    padre[padre[arco.first]] = padre[arco.second];
                else{
                    padre[padre[arco.first]] = padre[arco.second];
                    nodeRank[padre[arco.first]]++;
                }
                cluster--;
            }
        }
        S[peso] = cluster;
    }

    for(int i=0; i < T; i++){
        int peso;
        in >> peso;
        out << S[peso] << endl;
    }
}
