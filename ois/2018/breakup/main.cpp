#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int N, M;
vector<pair<int, int> > grafo[MAXN];
vector<int> inverseGraph[MAXN];
bool withW[MAXN];

bool needSwap(int node){
    int S = 0;
    for(auto i:grafo[node])
        S+= ((withW[i.first] == withW[node])*2 - 1) * i.second;
    return S < 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(false);
    cin>>N>>M;
    fill(withW, withW + N - 1, 1);
    for(int i = 0; i < M; i++){
        int da, a, v;
        cin>>da>>a>>v;
        grafo[da].push_back({a, v});
        inverseGraph[a].push_back(da);
    }
    unordered_set<int> wantSwitch;
    for(int i = 1; i < N - 1; i++)
        if(needSwap(i))
            wantSwitch.insert(i);

    while(!wantSwitch.empty()){
        int i = *wantSwitch.begin();
        wantSwitch.erase(wantSwitch.begin());
        withW[i] = 0;
        for(auto j:inverseGraph[i]){
            if(j != 0 && j != N - 1 && withW[j] && needSwap(j)){
                wantSwitch.insert(j);
            }
        }
    }
    for(int i = 0; i < N; i++)
        cout<<((withW[i])?'W':'G');
}
