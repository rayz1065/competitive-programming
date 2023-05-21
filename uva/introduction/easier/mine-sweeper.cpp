#include <bits/stdc++.h>
#define MAXN 105
using namespace std;

int N, M;
bool mappa[MAXN][MAXN];
bool visited[MAXN][MAXN];
int movR[] = {-1, -1, -1, +0, +1, +1, +1, +0};
int movC[] = {-1, +0, +1, +1, +1, +0, -1, -1};

void lose(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++)
            if(mappa[i][j])
                visited[i][j] = true;
    }
}

void init(){
    cin >> N;
    M = N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            char c;
            cin >> c;
            mappa[i][j] = (c == '*');
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            char c;
            cin >> c;
            visited[i][j] = (c == 'x');
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(visited[i][j] && mappa[i][j]){
                lose();
                return ;
            }
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
    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        if(t > 1)
            fprintf(out, "\n");

        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(!visited[i][j])
                    fprintf(out, ".");
                else if(mappa[i][j])
                    fprintf(out, "*");
                else
                    fprintf(out, "%c", calcola(i, j) + '0');
            }
            fprintf(out, "\n");
        }
    }
}
