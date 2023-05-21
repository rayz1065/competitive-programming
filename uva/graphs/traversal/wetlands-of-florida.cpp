#include <bits/stdc++.h>
#define MAXN 200
using namespace std;

bool visited[MAXN][MAXN];
bool acqua[MAXN][MAXN];

int movR[] = {-1, -1, -1, +0, +1, +1, +1, +0};
int movC[] = {-1, -0, +1, +1, +1, +0, -1, -1};

int N, M;

char input[MAXN];

vector<pair<int, int>> ricerca;

int length(char *A, char *B){
    int S = 0;
    while(S < B - A && A[S] != '\0')
        S++;
    return S;
}

int readInt(char *A, char *B, int &i){
    int S = 0;
    while(i < B - A && A[i] != '\0' && (A[i] < '0' || A[i] > '9'))
        i++;
    while(i < B - A && A[i] != '\0' && (A[i] >= '0' && A[i] <= '9'))
        S = S*10 + A[i] - '0', i++;
    return S;
}

void init(){
    ricerca.clear();
    for(int i = 0; i < MAXN; i++)
        fill(visited[i], visited[i] + MAXN, false);
    for(int i = 0; i < MAXN; i++)
        fill(acqua[i], acqua[i] + MAXN, false);

    do{
        cin >> input;
    } while(input == "\n");
    cin.ignore();

    N = 0;
    M = length(input, input + MAXN);

    while(input[0] == 'L' || input[0] == 'W'){
        for(int j = 0; j < MAXN && input[j] != '\0'; j++)
            acqua[N][j] = (input[j] == 'W');
        N++;
        cin.getline(input, MAXN);
    }
    while(input[0] < '0' || input[0] > '9'){
        cin.getline(input, MAXN);
    }
    while(input[0] >= '0' && input[0] <= '9'){
        int i = 0;
        int A = readInt(input, input + MAXN, i);
        int B = readInt(input, input + MAXN, i);

        ricerca.push_back({A - 1, B - 1});

        cin.getline(input, MAXN);
    }
}

inline bool inRange(int r, int c){
    return (r >= 0 && c >= 0 && r < N && c < M);
}

int visita(int r, int c){
    visited[r][c] = true;
    int S = 1;
    for(int m = 0; m < 8; m++){
        if(inRange(r + movR[m], c + movC[m]) && acqua[r + movR[m]][c + movC[m]] && !visited[r + movR[m]][c + movC[m]])
            S+= visita(r + movR[m], c + movC[m]);
    }
    return S;
}

int main(){
    int T;
    cin >> T;

    FILE *out = stdout;

    for(int t = 1; t <= T; t++){
        if(t > 1)
            fprintf(out, "\n");
        init();

        for(auto i:ricerca){
            memset(visited, 0, sizeof(visited));
            fprintf(out, "%d\n", visita(i.first, i.second));
        }
    }
}
