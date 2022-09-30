#include <bits/stdc++.h>
#define MAXN 20
#define MAXNODES 1050000
using namespace std;

int N, K;
bitset<MAXN> intoccate[MAXN];
int dist[MAXNODES];

void bfs(bitset<MAXN> node){
    queue<bitset<MAXN> > ff;
    fill(dist, dist + MAXNODES, 10000);
    ff.push(node);
    dist[node.to_ulong()] = 0;
    while(!ff.empty()){
        node = ff.front();
        ff.pop();
        for(int i = 0; i < N; i++){
            if(!node[i]){
                bitset<MAXN> nextNode = node & intoccate[i];
                nextNode[i] = true;
                if(dist[node.to_ulong()] + 1 < dist[nextNode.to_ulong()]){
                    ff.push(nextNode);
                    dist[nextNode.to_ulong()] = dist[node.to_ulong()] + 1;
                }
            }
        }
    }
}

int main(){
    cin>>N>>K;
    bitset<MAXN> situazioneIniziale;

    for(int i = 0; i < N; i++){
        bool ac;
        cin>>ac;
        situazioneIniziale[i] = ac;
    }

    for(int i = 0; i < N; i++){
        int M;
        cin>>M;
        intoccate[i].set();
        for(int j = 0; j < M; j++){
            int l;
            cin>>l;
            intoccate[i][l - 1] = false;
        }
    }

    bfs(situazioneIniziale);

    cout<<dist[1<<(K - 1)];
}
