#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int R, C;
string nome;
int H[MAXN][MAXN];

int movR[] = {0, 1, 0, -1}, movC[] = {1, 0, -1, 0};

set<pair<int, pair<int, int>>> ord;
int S[MAXN][MAXN];

bool inRange(int r, int c){
    return (r >= 0 && c >= 0 && r < R && c < C);
}

void init(){
    ord.clear();
    cin >> nome >> R >> C;
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++)
            cin >> H[r][c], ord.insert({H[r][c], {r, c}});
    }
}

int getH(int r, int c){
    if(!inRange(r, c))
        return INT_MAX/2;
    return H[r][c];
}

int solve(){
    int bestS = 0;

    for(auto i:ord){
        int r = i.second.first, c = i.second.second;
        S[r][c] = 1;
        for(int m = 0; m < 4; m++){
            if(H[r][c] > getH(r + movR[m], c + movC[m])){
                S[r][c] = max(S[r][c], S[r + movR[m]][c + movC[m]] + 1);
                bestS = max(bestS, S[r][c]);
            }
        }
    }
    return bestS;
}

int main(){
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();

        cout<<nome<<": "<<solve()<<"\n";
    }
}
