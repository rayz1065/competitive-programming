#include <bits/stdc++.h>
#define MAXN 105
using namespace std;

int N, M;
bool mappa[MAXN][MAXN];
int movR[] = {-1, -1, -1, +0, +1, +1, +1, +0};
int movC[] = {-1, +0, +1, +1, +1, +0, -1, -1};

void init(){
    cin >> N >> M;
    if(N == 0)
        return ;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            char c;
            cin >> c;
            mappa[i][j] = (c == '*');
        }
    }
}

inline bool inRange(int r, int c){
    return (r >= 0 && c >= 0 && r < N && c < M);
}

int calcola(int r, int c){
    int S = 0;
    for(int m = 0; m < 8; m++){
        if(inRange(r + movR[m], c + movC[m]) && mappa[r + movR[m]][c + movC[m]])
            S++;
    }
    return S;
}

int main(){
    FILE *out = stdout;

    for(int t = 1;; t++){
        init();
        if(N == 0)
            return 0;
        if(t > 1)
            fprintf(out, "\n");

        fprintf(out, "Field #%d:\n", t);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(mappa[i][j])
                    fprintf(out, "*");
                else
                    fprintf(out, "%c", calcola(i, j) + '0');
            }
            fprintf(out, "\n");
        }
    }
}
