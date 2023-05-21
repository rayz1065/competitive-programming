#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int N;
pair<int, int> cities[MAXN];

double adjMat[MAXN][MAXN];

double sqr(double x){
    return x*x;
}

double dist(pair<int, int> A, pair<int, int> B){
    return sqrt(sqr(A.first - B.first) + sqr(A.second - B.second));
}

void init(){
    cin >> N;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            adjMat[i][j] = 1e09;

    for(int i = 0; i < N; i++)
        cin >> cities[i].first >> cities[i].second;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(dist(cities[i], cities[j]) <= 10.00)
                adjMat[i][j] = dist(cities[i], cities[j]);
        }
    }
}

double solve(){
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);

    double S = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            S = max(S, adjMat[i][j]);

    return S;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        double S = solve();

        fprintf(out, "Case #%d:\n", t);
        if(S == 1e09)
            fprintf(out, "Send Kurdy\n\n");
        else fprintf(out, "%.4f\n\n", S);
    }
}
