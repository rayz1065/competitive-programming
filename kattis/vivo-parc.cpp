#include <iostream>
#include <vector>
#define MAXN 105
#define N_COLORS 4
using namespace std;

vector<int> grafo[MAXN];
bool visible[MAXN][MAXN];
int colore[MAXN];
int coloredNeighbors[MAXN][N_COLORS + 1];
int n;

void clearNode(int curr){
    int c = colore[curr];
    colore[curr] = 0;
    for(auto j:grafo[curr]){
        coloredNeighbors[j][c]--;
    }
}

void colorNode(int curr, int c){
    colore[curr] = c;
    for(auto j:grafo[curr]){
        coloredNeighbors[j][c]++;
    }
}

int saturation(int i){
    int s = 0;
    for(int j = 1; j <= N_COLORS; j++){
        if(coloredNeighbors[i][j] > 0)
            s++;
    }
    return s;
}

bool solve(){
    int bestNode = -1;
    for(int i = 0; i < n; i++){
        if(colore[i] == 0){
            int am = saturation(i);
            if(am == N_COLORS) return false;

            if(bestNode == -1 || (grafo[bestNode].size() < N_COLORS && grafo[i].size() >= N_COLORS) || am > saturation(bestNode)){
                bestNode = i;
            }
        }
    }

    if(bestNode == -1)
        return true;

    for(int j = 1; j <= N_COLORS; j++){
        if(coloredNeighbors[bestNode][j] == 0){
            colorNode(bestNode, j);
            if(solve()) return true;
            clearNode(bestNode);
        }
    }
    return false;
}

int main(){
    cin >> n;
    int a, b;
    char c;
    while(cin>>a>>c>>b){
        a--, b--;
        if(!visible[a][b]){
            visible[a][b] = true;
            visible[b][a] = true;
            grafo[a].push_back(b);
            grafo[b].push_back(a);
        }
    }

    solve();

    for(int i = 0; i < n; i++){
        cout<<i + 1<<" "<<colore[i]<<"\n";
    }
}
