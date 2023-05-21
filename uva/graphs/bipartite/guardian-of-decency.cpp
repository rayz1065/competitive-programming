#include <bits/stdc++.h>
#define MAXN 505

using namespace std;

struct pupil{
    int height;
    char mf;
    string music;
    string sport;

    bool operator < (const pupil B) const{
        return mf < B.mf;
    }
} pupils[MAXN];

int N;
vector<int> grafo[MAXN];
int adjMat[MAXN][MAXN];
int s, t;

void init(){
    cin >> N;

    for(int i = 0; i <= N + 1; i++)
        grafo[i].clear(), fill(adjMat[i], adjMat[i] + N + 2, 0);

    for(int i = 0; i < N; i++){
        cin >> pupils[i].height >> pupils[i].mf >> pupils[i].music >> pupils[i].sport;
    }

    s = 0, t = N + 1;
}

bool comp(pupil A, pupil B){
    if(abs(A.height - B.height) > 40)
        return false;
    if(A.mf == B.mf)
        return false;
    if(A.music != B.music)
        return false;
    if(A.sport == B.sport)
        return false;
    return true;
}

void generaGrafo(){
    for(int i = 0; i < N; i++){
        if(pupils[i].mf == 'M')
            grafo[s].push_back(i + 1), adjMat[s][i + 1] = 1;
        else
            grafo[i + 1].push_back(t), adjMat[i + 1][t] = 1;

        for(int j = 0; j < N; j++){
            if(comp(pupils[i], pupils[j]))
                grafo[i + 1].push_back(j + 1), adjMat[i + 1][j + 1] = (pupils[i].mf == 'M');
        }
    }
}

int dist[MAXN];
int bfsTree[MAXN];

bool findAugPath(){
    queue<int> FF;
    FF.push(0);

    fill(dist, dist + t + 1, INT_MAX >> 1);
    fill(bfsTree, bfsTree + t + 1, -1);

    dist[0] = 0;

    while(!FF.empty() && dist[t] == INT_MAX >> 1){
        int nodo = FF.front();
        FF.pop();

        for(auto i:grafo[nodo]){
            if(adjMat[nodo][i] > 0 && dist[i] == INT_MAX >> 1)
                dist[i] = dist[nodo] + 1, bfsTree[i] = nodo, FF.push(i);
        }
    }
    while(!FF.empty())
        FF.pop();
    return (dist[t] != INT_MAX >> 1);
}

int mf, f;

void augment(int nodo, int minArco){
    if(bfsTree[nodo] != -1){
        int da = bfsTree[nodo];
        augment(da, min(minArco, adjMat[da][nodo]));

        adjMat[da][nodo]-= f;
        adjMat[nodo][da]+= f;
    }
    else
        f = minArco;
}

int solve(){
    generaGrafo();

    mf = 0;
    while(findAugPath()){
        augment(t, INT_MAX >> 1);
        mf+= f;
    }
    return N - mf;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        fprintf(out, "%d\n", solve());
    }
}
