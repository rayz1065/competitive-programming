#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int N, M, A, B;
int collRimanenti;
vector<int> grafo[MAXN];
fstream in, out;

void print(vector<int> A){
    for(auto i:A)
        cout<<i<<" ";
    cout<<endl;
}

int getNext(int nodo){
    for(int j = 0; j < grafo[nodo].size(); j++){
        if(grafo[nodo][j] != B || grafo[B].size() > 1 || collRimanenti == 1){
            collRimanenti--;
            int v = grafo[nodo][j];
            grafo[nodo].erase(grafo[nodo].begin() + j, grafo[nodo].begin() + 1 + j);
            for(int a = 0; a < grafo[v].size(); a++){
                if(grafo[v][a] == nodo){
                    grafo[v].erase(grafo[v].begin() + a, grafo[v].begin() + a + 1);
                    break;
                }
            }
            out<<nodo<<" "<<v<<endl;
            return v;
        }
    }
    return -1;
}

int main(){
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N >> M >> A >> B;
    for(int i = 0; i < M; i++){
        int a, b;
        in >> a >> b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }

    collRimanenti = M;

    int nodo = A;
    while(collRimanenti > 0 && nodo != -1){
        nodo = getNext(nodo);
    }
}
