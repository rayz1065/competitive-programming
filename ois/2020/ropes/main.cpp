#include <bits/stdc++.h>
#pragma GCC optimize ("O3")

#define MAXN 100005
#ifndef _WIN32
    #define getchar() getchar_unlocked()
#endif // _WIN32

using namespace std;

int n;
vector<int> grafo[MAXN];

int cost[MAXN];
int time_req[MAXN];

int solve(int node){
    if(grafo[node].size() == 0)
        return 0;

    int best = 0, s = 0;

    for(auto &i:grafo[node]){
        s+= solve(i) + time_req[i];
        best = max(best, time_req[i]);
    }

    return cost[node] = s - best;
}

void read_int(int &n){
    n = 0;
    char c = getchar();
    while(c < '0') c = getchar();
    while(c >= '0')
        n = n * 10 + c - '0', c = getchar();
}

void init(){
    int p;
    read_int(n);
    for(int i = 1; i <= n; i++){
        read_int(p);
        grafo[p].push_back(i);
    }

    for(int i = 1; i <= n; i++)
        read_int(time_req[i]);
}

int main(){
    init();
    cout<<solve(0)<<"\n";
}
