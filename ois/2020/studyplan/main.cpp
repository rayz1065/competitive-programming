#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int h[MAXN];
int root = MAXN - 1;

vector<int> grafo[MAXN];

bool visited[MAXN];
int req[MAXN];
int min_time[MAXN];

stack<int> ts;

void topo_sort(int nodo){
    if(visited[nodo])
        return ;

    visited[nodo] = true;
    for(auto i:grafo[nodo])
        topo_sort(i);

    ts.push(nodo);
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> h[i];

    for(int i = 0; i < n; i++){
        cin >> req[i];

        for(int j = 0; j < req[i]; j++){
            int a;
            cin >> a;
            grafo[a].push_back(i);
        }

        req[i]++;
    }
    // h[root] = 0;
    for(int i = 0; i < n; i++)
        grafo[root].push_back(i);

    topo_sort(root);
    stack<int> tsrv;


    while(!ts.empty()){
        int i = ts.top();
        ts.pop();

        for(auto j:grafo[i]){
            min_time[j] = max(min_time[j], min_time[i] + h[i]);
        }

        tsrv.push(i);
    }

    int end_time = 0;
    for(int i = 0; i < n; i++)
        end_time = max(end_time, min_time[i] + h[i]);

    while(!tsrv.empty()){
        int i = tsrv.top();
        tsrv.pop();

        int s = end_time - h[i];

        for(auto j:grafo[i]){
            s = min(s, min_time[j] - h[i]);
        }
        min_time[i] = s;
    }

    for(int i = 0; i < n; i++)
        cout<<min_time[i]<<" ";
    cout<<"\n";
}
