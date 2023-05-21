#include <bits/stdc++.h>
#define MAXN 30

using namespace std;

int N;

int adjMat[MAXN*2][MAXN*2];
string nome[MAXN][MAXN];

int s = MAXN*2 - 2, t = MAXN*2 - 1;

void fixName(string &name){
    for(int i = 1; i < name.length(); i++)
        name[i] = tolower(name[i]);
    name[0] = toupper(name[0]);
}

void init(){
    cin >> N;

    memset(adjMat, 0, sizeof(adjMat));

    for(int i = 0; i < N; i++){
        int k;
        cin >> k;

        adjMat[s][i] = 1;

        for(int j = 0; j < k; j++){
            string n;
            cin >> n;
            fixName(n);

            nome[i][n[0] - 'A'] = n;

            adjMat[i][n[0] - 'A' + MAXN] = 1;
        }
    }

    for(int i = 0; i < N; i++){
        adjMat[i + MAXN][t] = 1;
    }

    /*for(int i = 0; i < MAXN*2; i++){
        bool found = false;
        for(int j = 0; j < MAXN*2; j++){
            if(adjMat[i][j] > 0)
                found = true;
        }
        if(found){
            cout<<i<<" => ";
            for(int j = 0; j < MAXN*2; j++){
                if(adjMat[i][j] > 0)
                    cout<<j<<" ";
            }
            cout<<"\n";
        }
    }*/
}

int dist[MAXN*2];
int bfsTree[MAXN*2];

bool findAugPath(int nodo, int arr){
    fill(dist, dist + 2*MAXN, INT_MAX>>1);
    fill(bfsTree, bfsTree + 2*MAXN, -1);
    dist[nodo] = 0;

    queue<int> FF;
    FF.push(nodo);

    while(!FF.empty()){
        nodo = FF.front();
        FF.pop();

        if(nodo == arr){
            while(!FF.empty())
                FF.pop();
            return true;
        }

        for(int i = 0; i < 2*MAXN; i++){
            if(adjMat[nodo][i] > 0 && dist[i] == INT_MAX>>1){
                FF.push(i);
                dist[i] = dist[nodo] + 1;
                bfsTree[i] = nodo;
            }
        }
    }
    return false;
}

bool findAugPath(){
    return findAugPath(s, t);
}

int mf, f;

void augment(int nodo, int arcoMin){
    if(bfsTree[nodo] == -1)
        f = arcoMin;
    else{
        int da = bfsTree[nodo];
        augment(da, min(arcoMin, adjMat[da][nodo]));

        adjMat[da][nodo]-= f;
        adjMat[nodo][da]+= f;
    }
}

string S[MAXN];

void solve(){
    mf = 0;
    while(findAugPath()){
        f = 0;
        augment(t, INT_MAX>>1);
    }

    for(int i = 0; i < N; i++){
        int nodo = i + MAXN;

        bool found = false;
        for(int j = 0; j < N && !found; j++){
            if(adjMat[nodo][j] > 0)
                found = true, S[i] = nome[j][i];
        }
    }
}

int main(){
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        solve();
        cout<<"Case #"<<t<<":\n";
        for(int i = 0; i < N; i++)
            cout<<S[i]<<"\n";
    }
}
