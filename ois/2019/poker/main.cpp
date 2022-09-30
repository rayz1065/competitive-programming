#include <bits/stdc++.h>
#define MAXP 1000000005
#define MAXN 100005
#define MAXT 1005
#define MAXG 1005
using namespace std;

struct info{
    int giorno;
    int inizio;
    int fine;
    int prezzo;
    int guadagno;
};

vector<vector<info> > gare[MAXG];
int soldiMax[MAXG + 1][MAXT];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin>>N>>M;

    for(int i = 0; i < N; i++){
        info gara;
        cin>>gara.giorno>>gara.inizio>>gara.fine>>gara.prezzo>>gara.guadagno;
        if(gare[gara.giorno].size() == 0)
            gare[gara.giorno].resize(MAXT);
        gare[gara.giorno][gara.inizio].push_back({gara});
    }

    soldiMax[0][0] = M;
    for(int i = 0; i < MAXG; i++){
        if(gare[i].size() == 0){
            for(int j = 0; j < MAXT; j++)
                soldiMax[i][j] = soldiMax[i][0];
        }
        else{
            for(int t = 0; t < MAXT; t++){
                soldiMax[i][t] = max(soldiMax[i][t], soldiMax[i][t - 1]);
                if(gare[i][t].size() > 0){
                    for(auto g:gare[i][t]){
                        if(g.prezzo <= soldiMax[i][t]){
                            soldiMax[i][g.fine] = max(soldiMax[i][g.fine], soldiMax[i][t] - g.prezzo + g.guadagno);
                        }
                    }
                }
            }
        }
        soldiMax[i + 1][0] = soldiMax[i][MAXT - 1];
    }

    cout<<soldiMax[MAXG - 1][MAXT - 1];
}
