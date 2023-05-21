#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int K, M, N;
double adjMat[MAXN][MAXN];

struct isola{
    int x;
    int y;
    int r;
} posizioni[MAXN];

double sq(double x){
    return x*x;
}

double getDist(isola A, isola B){
    return sqrt(sq(A.x - B.x) + sq(A.y - B.y)) - (A.r + B.r);
}

bool init(){
    if(!(cin >> K >> M))
        return false;

    int x, y, r;
    for(int i = 0; i < 2; i++){
        cin >> x >> y >> r;
        posizioni[i] = {x, y, r};
    }

    cin >> N;
    N+= 2;

    for(int i = 2; i < N; i++){
        cin >> x >> y >> r;
        posizioni[i] = {x, y, r};
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            adjMat[i][j] = getDist(posizioni[i], posizioni[j]);
        adjMat[i][i] = 0;
    }

    /*cout<<"\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            cout<<adjMat[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";*/
    return true;
}

bool solve(){
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                adjMat[i][j] = min(adjMat[i][j], max(adjMat[i][k], adjMat[k][j]));


    /*cout<<"\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            cout<<adjMat[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";*/

    return (adjMat[0][1] > M*K);
}

int main(){
    FILE *out = stdout;

    while(init()){
        fprintf(out, "%s\n", solve() ? "Larry and Ryan will be eaten to death." : "Larry and Ryan will escape!");
    }
}
