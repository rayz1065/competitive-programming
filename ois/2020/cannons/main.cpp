#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n;
int t[MAXN];
int dist[MAXN];
bool visited[MAXN];

queue<int> ff;

void fill_loop(int node, int d){
    while(dist[node] == -1)
        dist[node] = d, ff.push(node), node = t[node];
}

int solve(){
    while(!ff.empty())
        ff.pop();

    fill(dist, dist + n, -1);
    fill(visited, visited + n, false);
    ff.push(0);
    fill_loop(0, 0);

    while(!ff.empty()){
        //cout<<node<<" "<<dist[node]<<"\n";
        int node = ff.front();
        ff.pop();
        if(visited[node]) continue;
        visited[node] = true;
        fill_loop(node, dist[node]);

        if(node + 1 < n && dist[node + 1] == -1){
            fill_loop(node + 1, dist[node] + 1);
        }
        if(node > 0 && dist[node - 1] == -1){
            fill_loop(node - 1, dist[node] + 1);
        }
    }

    return dist[n - 1];
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> t[i];

    cout<<solve();
}
