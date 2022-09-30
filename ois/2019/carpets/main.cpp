#include <bits/stdc++.h>
#ifdef _WIN32
    #define getchar_unlocked getchar
#endif // _WIN32
#define MAXR 2018
#define MAXK 10005
using namespace std;

int N, M, K;
int top[MAXK], lft[MAXK], bottom[MAXK], rght[MAXK];

int fastIn(){
    int S = 0;
    char c;
    c = getchar_unlocked();
    while(c >= '0'){
        S = S*10 + c - '0';
        c = getchar_unlocked();
    }
    return S;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    N = fastIn();
    M = fastIn();
    K = fastIn();

    fill(top, top + K + 1, -1);
    fill(bottom, bottom + K + 1, 2*N);
    fill(lft, lft + K + 1, 2*M);
    fill(rght, rght + K + 1, -1);

    for(int i = N - 1; i >= 0; i--){
        for(int j = 0; j < M; j++){
            int c = fastIn();
            top[c] = max(top[c], i);
            bottom[c] = min(bottom[c], i);
            lft[c] = min(lft[c], j);
            rght[c] = max(rght[c], j);
        }
    }

    for(int i = 1; i <= K; i++)
        cout<<lft[i]<<" "<<bottom[i]<<" "<<rght[i] + 1<<" "<<top[i] + 1<<"\n";
}
