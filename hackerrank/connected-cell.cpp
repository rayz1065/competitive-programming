#include <bits/stdc++.h>
#define MAXN 15
using namespace std;

int N, M;
bool explored[MAXN][MAXN];
int direR[] = {-1, -1, 0, 1, 1, 1, 0, -1}, direC[] = {0, 1, 1, 1, 0, -1 -1 -1};

bool inRange(int R, int C){
    return (R >= 0 && C >= 0 && R < N && C < M);
}

int explore(int R, int C){
    stack<pair<int, int> > FF;
    FF.push({R, C});
    explored[R][C] = true;
    int S = 0, r, c;
    while(!FF.empty()){
        R = FF.top().first;
        C = FF.top().second;
        FF.pop();
        S++;
        for(int i = 0; i < 8; i++){
            r = R + direR[i], c = C + direC[i];
            if(inRange(r, c) && !explored[r][c]){
                FF.push({r, c});
                explored[r][c] = true;
            }
        }
    }
    return S;
}

int main(){
    cin>>N>>M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin>>explored[i][j];
            explored[i][j] = 1 - explored[i][j];
        }
    }
    int S = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(!explored[i][j])
                S = max(S, explore(i, j));
        }
    }
    cout<<S;
}
