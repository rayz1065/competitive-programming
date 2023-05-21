#include <bits/stdc++.h>
#define MAXN 505
using namespace std;

int N;
string keys[MAXN];
map<string, int> dist;

void init(){
    dist.clear();
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> keys[i];
        while(keys[i].length() < 4)
            keys[i] = '0' + keys[i];
        dist[keys[i]] = INT_MAX/2;
    }
}

int getDist(string A, string B){
    int S = 0;
    for(int i = 0; i < 4; i++)
        S+= min((A[i] - B[i] + 10)%10, (B[i] - A[i] + 10)%10);
    return S;
}

void aggiungi(string A){
    dist[A] = 0;
    for(int i = 0; i < N; i++)
        dist[keys[i]] = min(dist[keys[i]], getDist(A, keys[i]));
}

int solve(){
    int best = 0;
    for(int i = 1; i < N; i++){
        if(getDist(keys[best], "0000") > getDist(keys[i], "0000")){
            best = i;
        }
    }

    int S = 0;

    S+= getDist(keys[best], "0000");
    aggiungi(keys[best]);

    for(int a = 1; a < N; a++){
        int best = 0;
        while(best < N && dist[keys[best]] == 0)
            best++;
        if(best == N){
            return S;
        }
        for(int i = best + 1; i < N; i++){
            if(dist[keys[i]] != 0 && dist[keys[i]] < dist[keys[best]])
                best = i;
        }
        S+= dist[keys[best]];
        aggiungi(keys[best]);
    }

    return S;
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        fprintf(out, "%d\n", solve());
    }
}
