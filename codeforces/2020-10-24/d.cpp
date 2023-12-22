#include <bits/stdc++.h>
#define MAXN 200005
#define ROOT_NODE 0

using namespace std;

int n, m;
int a[MAXN];
int padre[MAXN];
vector<int> figli[MAXN];

typedef long long int lli;

struct nodeInfo{
    int foglie;
    lli mag;
    lli somma;
};

void init(){
    cin >> n;
    m = n - 1;
    for(int i = 1; i < n; i++){
        cin >> padre[i];
        padre[i]--;
        figli[padre[i]].push_back(i);
    }
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
}

nodeInfo calcNode(int i){
    if(figli[i].size() == 0) // foglia
        return {1, a[i], a[i]};

    nodeInfo sol = {0, 0, a[i]};
    for(auto j:figli[i]){
        nodeInfo curr = calcNode(j);
        sol.foglie+= curr.foglie;
        sol.mag = max(sol.mag, curr.mag);
        sol.somma+= curr.somma;
    }

    //cout<<sol.mag * sol.foglie<<" < "<<sol.somma<<" ?\n";
    if(sol.mag * sol.foglie < sol.somma){
        //cout<<"yes\n";
        if(sol.somma % sol.foglie == 0)
            sol.mag = sol.somma/sol.foglie;
        else
            sol.mag = sol.somma/sol.foglie + 1;
    }

    //cout<<"Nodo "<<i<<": "<<sol.mag<<", "<<sol.somma<<" ("<<sol.foglie<<")"<<"\n";

    return sol;
}

lli solve(){
    nodeInfo sol = calcNode(ROOT_NODE);
    return sol.mag;
}

int main(){
    init();
    cout<<solve()<<"\n";
}
