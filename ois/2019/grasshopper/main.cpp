#include <bits/stdc++.h>
#ifdef _WIN32
    #define getchar_unlocked getchar
#endif // _WIN32
#define MAXN 100001
#define MAXM 1000000
using namespace std;

int N, M;
vector<int> grafo[MAXN];
bool visited[2][MAXN];

int fastIn(){
    int S = 0;
    char c;
    c = getchar_unlocked();
    while(c >= '0'){
        S = S*10 + c - '0';
        c = getchar_unlocked();
    }
    return S;
}

void visita(int nodo, bool aria){
    visited[aria][nodo] = true;
    for(auto i:grafo[nodo]){
        if(!visited[1 - aria][i])
            visita(i, 1 - aria);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    N = fastIn();
    M = fastIn();

    for(int i = 0; i < M; i++){
        int da, a;
        da = fastIn();
        a = fastIn();
        grafo[da].push_back(a);
    }

    visita(0, 0);

    int visitabili = 0;
    for(int i = 0; i < N; i++)
        visitabili+= visited[0][i];

    cout<<visitabili<<endl;
}
