#include <bits/stdc++.h>
#define MAXN 10005
#define MAXM 10005
using namespace std;

typedef pair<int, int> pii;
pii piatti[MAXN];
int fuochi[MAXM], libero[MAXN], sol[MAXN];

bool gt(const pii a, const pii b){
    return (a.first > b.first);
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int N, M;

    cin >> N >> M;
    for(int i = 0; i < N; i++){
        int p;
        cin >> p;
        piatti[i] = {p, i};
    }
    for(int i = 0; i < M; i++)
        cin >> fuochi[i];
    sort(piatti, piatti + N, gt);

    for(int i = 0; i < N; i++){
        int best = 0, bestEnd = INT_MAX;
        for(int j = 0; j < M; j++){
            if(libero[j] + piatti[i].first*fuochi[j] < bestEnd)
                bestEnd = libero[j] + piatti[i].first*fuochi[j], best = j;
        }
        libero[best] = bestEnd, sol[piatti[i].second] = best;
    }
    cout<<*max_element(libero, libero + M)<<endl;
    for(int i = 0; i < N; i++)
        cout<<sol[i]<<" ";
    cout<<endl;
}
