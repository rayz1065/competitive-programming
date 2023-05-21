#include <bits/stdc++.h>
#define MAXC 100

using namespace std;

const int N = 8;
char griglia[N][N];
bool occ[N][N];
bool attaccata[N][N];

void init(char input[]){
    int r = 0, c = 0;
    memset(occ, false, sizeof(occ));
    memset(attaccata, false, sizeof(attaccata));
    memset(griglia, '/', sizeof(griglia));

    for(int i = 0; i < MAXC && input[i] != '\0'; i++){
        if(input[i] == '/')
            r++, c = 0;
        else if('0' <= input[i] && input[i] <= '9')
            c+= input[i] - '0';
        else{
            griglia[r][c] = input[i];
            occ[r][c] = true;
            c++;
        }
    }
}

void stampa(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            cout<<((occ[i][j])?griglia[i][j]:'-')<<" ";
        cout<<"\n";
    }
    cout<<"\n";
}

bool singleMove(char c){
    c = tolower(c);
    return (c == 'n' || c == 'k' || c == 'p');
}

inline bool inRange(int r, int c){
    return (r >= 0 && c >= 0 && r < N && c < N);
}

void espandi(int r, int c){
    if(!occ[r][c])
        return ;
/**
    r - torre
    n - cavallo
    b - alfiere
    q - regina
    k - re
    p - pedone
**/
    vector<pair<int, int>> mosse;
    if(singleMove(griglia[r][c])){
        if(griglia[r][c] == 'p')
            mosse = {{1, -1}, {1, 1}};
        else if(griglia[r][c] == 'P')
            mosse = {{-1, -1}, {-1, 1}};
        else if(tolower(griglia[r][c]) == 'n')
            mosse = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
        else if(tolower(griglia[r][c]) == 'k')
            mosse = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

        for(auto i:mosse){
            if(inRange(r + i.first, c + i.second) && !occ[r + i.first][c + i.second]){
                //cout<<griglia[r][c]<<" da "<<r<<","<<c<<" a "<<r + i.first<<","<<c + i.second<<"\n";
                attaccata[r + i.first][c + i.second] = true;
            }
        }
        return ;
    }
    if(tolower(griglia[r][c]) == 'r'){
        mosse = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
    }
    if(tolower(griglia[r][c]) == 'q'){
        mosse = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    }
    if(tolower(griglia[r][c]) == 'b'){
        mosse = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    }

    for(auto i:mosse){
        for(int newR = r + i.first, newC = c + i.second; inRange(newR, newC) && !occ[newR][newC]; newR+= i.first, newC+= i.second){
            //cout<<griglia[r][c]<<" da "<<r<<","<<c<<" a "<<newR<<","<<newC<<"\n";
            attaccata[newR][newC] = true;
        }
    }
}

int main(){
    FILE *out = stdout;
    char input[MAXC];

    while(cin >> input){
        if(input[0] == '-')
            return 0;
        init(input);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                espandi(i, j);
            }
        }
        int S = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                S+= (!occ[i][j] && !attaccata[i][j]);
            }
        }
        fprintf(out, "%d\n", S);
    }
}
