#include <bits/stdc++.h>
#define MAXN 15
#define MAXM 30
#define MAXNODES 500
using namespace std;

const int s = 0, t = MAXNODES - 1, play = 1, tlay = (MAXN - 1) * MAXM;

int n, m;
vector<int> grafo[MAXNODES];
int adjmat[MAXNODES][MAXNODES];

void add_arco(int i, int j, int am){
    grafo[i].push_back(j);
    grafo[j].push_back(i);
    adjmat[i][j] = am;
}

void init(){
    cin >> n >> m;
    int curr[MAXM];
    for(int i = 0; i < MAXNODES; i++)
        grafo[i].clear();
    memset(adjmat, 0, sizeof(adjmat));

    for(int i = 0; i < n; i++){
        int laystart = i*MAXM + play;

        fill(curr, curr + m, 0);
        int a;
        cin >> a;
        while(a--){
            int col;
            cin >> col;
            col--;
            curr[col]++;
        }

        if(i == 0){
            for(int i = 0; i < m; i++){
                if(curr[i]) add_arco(s, laystart + i, curr[i]);
                add_arco(laystart + i, tlay + i, 1);
            }
        }
        else{
            for(int i = 0; i < m; i++){
                if(!curr[i])    add_arco(play + i, laystart + i, 1);
                if(curr[i] > 1) add_arco(laystart + i, play + i, curr[i] - 1);
            }
            for(int i = 0; i < m; i++){
                for(int j = 0; j < m; j++){
                    if(curr[j] == 0 && curr[i] > 1){
                        // j: carta mancante, i: carta doppiona
                        add_arco(laystart + j, laystart + i, 1);
                    }
                }
            }
        }
    }
    for(int i = 0; i < m; i++)
        add_arco(tlay + i, t, 1);

    /*for(int i = 0; i < MAXNODES; i++){
        if(grafo[i].size() > 0){
            cout<<i<<": ";
            for(auto j:grafo[i])
                cout<<"("<<j<<", "<<adjmat[i][j]<<") ";
            cout<<"\n";
        }
    }
    cout<<"\n";*/
}

int bfs_tree[MAXNODES], dist[MAXNODES];

bool find_aug(){
    memset(bfs_tree, (1<<8) - 1, sizeof(bfs_tree));
    memset(dist, 1, sizeof(dist));
    queue<int> ff;
    ff.push(s);
    dist[s] = 0;

    while(!ff.empty()){
        int node = ff.front();
        if(node == t)
            return true;
        ff.pop();

        for(auto i:grafo[node]){
            if(adjmat[node][i] > 0 && dist[i] > dist[node] + 1)
                bfs_tree[i] = node, dist[i] = dist[node] + 1, ff.push(i);
        }
    }
    return false;
}

int f, ftot;

void augment(int node){
    if(bfs_tree[node] != -1){
        // da dfs_tree[node] a node
        f = min(f, adjmat[bfs_tree[node]][node]);
        augment(bfs_tree[node]);
        adjmat[bfs_tree[node]][node]-= f;
        adjmat[node][bfs_tree[node]]+= f;
    }
}

int solve(){
    ftot = 0;
    while(find_aug()){
        f = INT_MAX >> 1;
        augment(t);
        ftot+= f;
    }
    return ftot;
}

//#define cout out

int main(){
    //fstream out;
    //out.open("output.txt", ios::out);

    int T;
    cin >> T;
    for(int t = 1; t <= T; t++){
        init();
        cout<<"Case #"<<t<<": "<<solve()<<"\n";
    }
}
