#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int N;
pair<double, double> punti[MAXN];
double dist[MAXN];
bool visited[MAXN];

void init(){
    cin >> N;
    for(int i = 0; i < N; i++){
        double x, y;
        cin >> x >> y;
        punti[i] = {x, y};
    }
    fill(dist, dist + N, INT_MAX/2);
    fill(visited, visited + N, false);
}

int findBestDist(){
    int best = -1;
    double bestDist = INT_MAX/2;

    for(int i = 0; i < N; i++)
        if(!visited[i] && dist[i] < bestDist)
            bestDist = dist[i], best = i;
    return best;
}

inline double sqr(double x){
    return x*x;
}

double getDist(int i, int j){
    return sqrt(sqr(punti[i].first - punti[j].first) + sqr(punti[i].second - punti[j].second));
}

void aggiungi(int nodo){
    visited[nodo] = true;
    for(int i = 0; i < N; i++)
        dist[i] = min(dist[i], getDist(nodo, i));
}

double solve(int da){
    double S = 0;
    aggiungi(da);

    for(int i = 1; i < N; i++){
        int a = findBestDist();
        assert(a >= 0);
        S+= dist[a];
        aggiungi(a);
    }

    return S;
}

double solve(){
    return solve(0);
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        if(t > 1)
            fprintf(out, "\n");
        init();
        fprintf(out, "%.2f\n", solve(0));
    }
}
