#include <bits/stdc++.h>
#define MAXN 30

using namespace std;

char inputTxt[100];

int readInt(char str[100], int &i){
    while(i < 100 && str[i] < '0' || str[i] > '9')
        i++;
    int n = 0;
    while(i < 100 && str[i] >= '0' && str[i] <= '9')
        n = n*10 + str[i++] - '0';
    return n;
}

vector<int> grafo[MAXN];
int daysReq[MAXN];

void init(){
    for(int i = 0; i < MAXN; i++)
        daysReq[i] = -1, grafo[i].clear();

    cin.getline(inputTxt, 100);
    while(inputTxt[0] < 'A' || inputTxt[0] > 'Z')
        assert(cin.getline(inputTxt, 100));

    while(inputTxt[0] >= 'A' && inputTxt[0] <= 'Z'){
        int da = inputTxt[0] - 'A';
        int i = 1;
        daysReq[da] = readInt(inputTxt, i);
        if(inputTxt[i] == ' '){
            i++;
            while(i < 100 && inputTxt[i] >= 'A' && inputTxt[i] <= 'Z')
                grafo[da].push_back(inputTxt[i++] - 'A');
        }
        cin.getline(inputTxt, 100);
    }
}

stack<int> topoSort;
bool visited[MAXN];
int dist[MAXN];

void compTopoSort(int nodo){
    visited[nodo] = true;
    for(auto i:grafo[nodo])
        if(!visited[i])
            compTopoSort(i);
    topoSort.push(nodo);
}

int solve(){
    fill(visited, visited + MAXN, false);
    for(int i = 0; i < MAXN; i++){
        if(daysReq[i] != -1 && !visited[i])
            compTopoSort(i);
    }

    fill(dist, dist + MAXN, INT_MAX >> 1);
    for(int i = 0 ; i < MAXN; i++)
        dist[i] = -daysReq[i];
    dist[topoSort.top()] = - daysReq[topoSort.top()];

    while(!topoSort.empty()){
        int nodo = topoSort.top();
        topoSort.pop();
        for(auto j:grafo[nodo]){
            dist[j] = min(dist[j], dist[nodo] - daysReq[j]);
        }
    }

    int minDist = *min_element(dist, dist + MAXN);
    return -minDist;
}

int main(){
    FILE *out = stdout;
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        if(t > 1)
            fprintf(out, "\n");
        init();
        fprintf(out, "%d\n", solve());
    }
}
