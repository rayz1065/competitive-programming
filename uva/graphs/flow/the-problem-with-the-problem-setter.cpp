#include <bits/stdc++.h>
#define MAXK 25
#define MAXP 1005
#define MAXN (MAXK + MAXP + 5)
#define CATIDX(x) (x + catlay)
#define PROBIDX(x) (x + problay)

using namespace std;

int s = 0, t = MAXN - 1, problay = 1, catlay = MAXP + 1;
int k, p, reqp;

vector<int> grafo[MAXN];
int adjmat[MAXN][MAXN];
int bfstree[MAXN];
int dist[MAXN];

void add_arco(int i, int j, int w){
    adjmat[i][j] = w;
    adjmat[j][i] = 0;
    grafo[j].push_back(i);
    grafo[i].push_back(j);
}

bool init(){
    cin >> k >> p;
    if(k == 0) return false;

    for(int i = 0; i < MAXN; i++)
        grafo[i].clear();
    memset(adjmat, 0, sizeof(adjmat));
    reqp = 0;

    for(int i = 0; i < k; i++){
        int incat;
        cin >> incat;
        add_arco(CATIDX(i), t, incat); // catlay to well
        reqp+= incat;
    }

    for(int i = 0; i < p; i++){
        int am;
        cin >> am;
        while(am--){
            int cat;
            cin >> cat;
            cat--;
            // problema i in cat cat
            add_arco(PROBIDX(i), CATIDX(cat), 1); // problay to catlay
        }
        add_arco(s, PROBIDX(i), 1); // source to problay
    }

    return true;
}

bool findaug(){
    queue<int> ff;
    ff.push(s);
    memset(dist, 1, sizeof dist);
    memset(bfstree, (1 << 8) - 1, sizeof bfstree);
    dist[s] = 0;

    while(!ff.empty()){
        int node = ff.front();
        ff.pop();

        if(node == t)
            return true;

        for(auto j:grafo[node]){
            if(adjmat[node][j] > 0 && dist[node] + 1 < dist[j])
                ff.push(j), dist[j] = dist[node] + 1, bfstree[j] = node;
        }
    }
    return false;
}

void augment(int node, int &f){
    if(bfstree[node] != -1){
        f = min(f, adjmat[bfstree[node]][node]);
        augment(bfstree[node], f);
        adjmat[bfstree[node]][node]-= f;
        adjmat[node][bfstree[node]]+= f;
    }
}

void solve(){
    int mf = 0;
    while(findaug()){
        int f = (INT_MAX >> 1);
        augment(t, f);
        mf+= f;
    }
    if(mf < reqp) cout<<0<<"\n";
    else{
        cout<<1<<"\n";

        for(int cat = 0; cat < k; cat++){
            int i = CATIDX(cat);
            bool p = false;
            for(auto j:grafo[i]){
                if(j >= problay && j < catlay && adjmat[i][j] == 1){
                    if(p) cout<<" ";
                    p = true;
                    cout<<j - problay + 1;
                }
            }
            cout<<"\n";
        }
    }
}

int main(){
    while(init())
        solve();
}
