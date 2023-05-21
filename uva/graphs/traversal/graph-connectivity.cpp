#include <bits/stdc++.h>
#define MAXN 30
using namespace std;

char maxEl;
bool visited[MAXN];
bool daa[MAXN][MAXN];

void init(){
    do{
        maxEl = getchar();
    } while(maxEl == '\n');

    for(int i = 0; i < MAXN; i++)
        fill(daa[i], daa[i] + MAXN, false);
    fill(visited, visited + MAXN, false);

    while(true){
        char i = getchar();
        if(i == '\n'){
            i = getchar();
            if(i == '\n' || i == EOF)
                return ;
        }
        char A = i, B = getchar();
        daa[A - 'A'][B - 'A'] = true;
        daa[B - 'A'][A - 'A'] = true;
    }
}

void dfs(int node){
    visited[node] = true;
    for(int i = 0; i < MAXN; i++){
        if(daa[node][i] && !visited[i])
            dfs(i);
    }
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        if(t > 1)
            fprintf(out, "\n");
        init();

        int S = 0;
        for(int i = 0; i <= maxEl - 'A'; i++){
            if(!visited[i])
                dfs(i), S++;
        }
        fprintf(out, "%d\n", S);
    }
}
