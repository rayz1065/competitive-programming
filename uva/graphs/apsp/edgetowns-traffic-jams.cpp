#include<bits/stdc++.h>
#define MAXN 105

using namespace std;

int N;
int adjMatOld[MAXN][MAXN];
int adjMatNew[MAXN][MAXN];

int A, B;

bool init(){
    cin >> N;
    if(N == 0)
        return false;

    for(int i = 1; i <= N; i++)
        fill(adjMatOld[i], adjMatOld[i] + N + 1, INT_MAX>>1),
        fill(adjMatNew[i], adjMatNew[i] + N + 1, INT_MAX>>1);
    for(int i = 1; i <= N; i++)
        adjMatOld[i][i] = adjMatNew[i][i] = 0;

    for(int i = 1; i <= N; i++){
        int a;
        cin >> a;
        assert(a == i);
        while(getchar() != '\n'){
            int b;
            cin >> b;
            adjMatOld[a][b] = 1;
        }
    }

    for(int i = 1; i <= N; i++){
        int a;
        cin >> a;
        assert(a == i);
        while(getchar() != '\n'){
            int b;
            cin >> b;
            adjMatNew[a][b] = 1;
        }
    }
    cin >> A >> B;
    return true;
}

void fillMat(int adjMat[][MAXN]){
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
}


bool solve(){
    fillMat(adjMatOld);
    fillMat(adjMatNew);

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++)
            if(A * adjMatOld[i][j] + B < adjMatNew[i][j])
                return false;
    }
    return true;
}

int main(){
    while(init()){
        printf("%s\n", solve() ? "Yes" : "No");
    }
}
