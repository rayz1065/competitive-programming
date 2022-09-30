#include <bits/stdc++.h>
#define MAXN 3005
using namespace std;

int N = 0;
pair<int, int> nodi[MAXN];
int dist[MAXN];

int sqr(int a){
    return a*a;
}

int getDist(int a, int b){
    return sqr(nodi[a].first - nodi[b].first) + sqr(nodi[a].second - nodi[b].second);
}

void gc(char &c){
    c = getchar_unlocked();
    while(c != '.' && c != 'T')
        c = getchar_unlocked();
}

int main(){
    int L;
    cin >> L;
    
    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            char c;
            gc(c);
            if(c == 'T')
                nodi[N++] = {i, j};
        }
    }

    for(int i = 0; i < N; i++)
        dist[i] = getDist(0, i);

    int S = 0;
    for(int dimIsola = 1; dimIsola < N; dimIsola++){
        int minDist = INT_MAX/2, b = 0;
        for(int i = 0; i < N; i++){
            if(dist[i] > 0 && dist[i] < minDist)
                minDist = dist[i], b = i;
        }
        S+= minDist;
        for(int i = 0; i < N; i++){
            dist[i] = min(dist[i], getDist(b, i));
        }
    }
    cout<<S<<"\n";
}