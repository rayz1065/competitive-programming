#include <bits/stdc++.h>
#define MAXN 30

using namespace std;

int adjMatY[MAXN][MAXN];
int adjMatM[MAXN][MAXN];

int Y, M;
int N = 26;

void addEdge(char yorm, int da, int a, int w){
    if(yorm == 'Y')
        adjMatY[da][a] = min(adjMatY[da][a], w);
    else
        adjMatM[da][a] = min(adjMatM[da][a], w);
}

bool init(){
    int archi;
    cin >> archi;
    if(archi == 0)
        return false;

    for(int i = 0; i < MAXN; i++)
        fill(adjMatY[i], adjMatY[i] + MAXN, INT_MAX>>1),
        fill(adjMatM[i], adjMatM[i] + MAXN, INT_MAX>>1);
    for(int i = 0; i < MAXN; i++)
        adjMatY[i][i] = adjMatM[i][i] = 0;

    for(int i = 0; i < archi; i++){
        char yorm, uorb, da, a;
        int w;
        cin >> yorm >> uorb >> da >> a >> w;

        addEdge(yorm, da - 'A', a - 'A', w);
        if(uorb == 'B')
            addEdge(yorm, a - 'A', da - 'A', w);
    }
    char y, m;
    cin >> y >> m;

    Y = y - 'A', M = m - 'A';
    return true;
}

void marshall(int adjMat[][MAXN]){
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
}

int main(){
    while(init()){
        marshall(adjMatM);
        marshall(adjMatY);

        int S = 1e09;
        for(int i = 0; i < N; i++){
            if(adjMatY[Y][i] + adjMatM[M][i] < S)
                S = adjMatY[Y][i] + adjMatM[M][i];
        }

        if(S == 1e09) cout<<"You will never meet.\n";
        else{
            cout<<S;
            for(int i = 0; i < N; i++){
                if(adjMatY[Y][i] + adjMatM[M][i] == S)
                    cout<<" "<<(char)(i + 'A');
            }
            cout<<"\n";
        }
    }
}
