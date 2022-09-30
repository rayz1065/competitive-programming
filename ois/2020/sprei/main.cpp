#include <bits/stdc++.h>
#define MAXN 10005
#define MAXM 105

using namespace std;

int n, m, b;

int coords[MAXN][MAXM];
long long int coordsum[MAXN];
vector<int> grafo[MAXN];

int match[MAXN];
bool visited[MAXN];

bool is_adj(int i, int j){
    if(abs(coordsum[i] - coordsum[j]) != 1)
        return false;

    int x = 0, *a = coords[i], *b = coords[j];

    while(x < m && a[x] == b[x]) x++;
    if(abs(a[x] - b[x]) > 1) return false;
    x++;
    while(x < m && a[x] == b[x]) x++;
    return x == m;
}

int mcmb_aug(int i){
    if(visited[i])
        return 0;
    visited[i] = true;

    for(auto j:grafo[i]){
        if(match[j] == -1 || mcmb_aug(match[j])){
            match[j] = i;
            return 1;
        }
    }
    return 0;
}

int mcbc(){
    memset(match, (1 << 8) - 1, sizeof match);

    int s = 0;
    for(int i = 0; i < n; i++){
        if(coordsum[i] & 1){
            memset(visited, 0, sizeof visited);
            s+= mcmb_aug(i);
        }
    }

    return s;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> b;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            cin >> coords[i][j], coordsum[i]+= coords[i][j];
    }

    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(is_adj(i, j)){
                if(coordsum[i] & 1) grafo[i].push_back(j);
                else                grafo[j].push_back(i);
            }

    cout<<mcbc()<<"\n";
}
