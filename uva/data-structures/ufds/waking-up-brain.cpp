#include <bits/stdc++.h>
#define MAXN 30
#define MAXM 500

using namespace std;

int n, m;

vector<int> grafo[MAXN];
bool is_awake[MAXN];
bool will_awake[MAXN];

int node(char c){
    return c - 'A';
}

bool init(){
    if(!(cin >> n >> m))
        return false;

    fill(is_awake, is_awake + MAXN, false);
    for(int i = 0; i < MAXN; i++)
        grafo[i].clear();

    string sv;
    cin >> sv;

    for(int i = 0; i < sv.length(); i++)
        is_awake[node(sv[i])] = true;

    for(int i = 0; i < m; i++){
        char ac, bc;
        cin >> ac >> bc;
        int a = node(ac), b = node(bc);
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    return true;
}

bool can_wake(int a){
    int s = 0;
    for(auto b:grafo[a])
        if(is_awake[b]) s++;
    return s >= 3;
}

bool sveglia_nodi(){
    bool f = false;

    fill(will_awake, will_awake + MAXN, false);

    for(int i = 0; i < MAXN; i++){
        if(!is_awake[i] && can_wake(i))
            f = true, will_awake[i] = true;
    }
    for(int i = 0; i < MAXN; i++){
        if(!is_awake[i] && will_awake[i])
            is_awake[i] = true;
    }

    return f;
}

int count_awake(){
    int s = 0;
    for(int i = 0; i < MAXN; i++)
        if(is_awake[i]) s++;

    return s;
}

int solve(){
    int t = 0;
    while(sveglia_nodi())
        t++;

    return (count_awake() == n) ? t : -1;
}

int main(){
    FILE *out = stdout;//fopen("output.txt", "w");

    while(init()){
        int s = solve();
        if(s == -1)
            fprintf(out, "THIS BRAIN NEVER WAKES UP\n");
        else
            fprintf(out, "WAKE UP IN, %d, YEARS\n", s);
    }
}
