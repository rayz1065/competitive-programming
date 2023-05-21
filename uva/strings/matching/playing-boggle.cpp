#include <bits/stdc++.h>
#define MAXM 105
#define MAXL 20
#define NUMDIRE 8

using namespace std;

const int n = 4;
int m;

char lettere[n][n];
char dict[MAXM][MAXL];
int word_len[MAXM];

bool used[n][n];

int movr[] = {-1, -1, 0, 1, 1, 1, 0, -1},
    movc[] = {0, 1, 1, 1, 0, -1, -1, -1};

int score_per_len(int l){
    static const int spl[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};
    if(l > 8) l = 8;
    return spl[l];
}

inline bool in_range(int r, int c){
    return (r >= 0 && c >= 0 && r < n && c < n);
}

void init(){
    for(int i = 0; i < n; i++)
        cin >> lettere[i];

    cin >> m;

    for(int i = 0; i < m; i++)
        cin >> dict[i], word_len[i] = strlen(dict[i]);
}

bool _solve(int p, int i, int r, int c){
    if(lettere[r][c] != dict[p][i])
        return false;
    if(i == word_len[p] - 1)
        return true;

    used[r][c] = true;

    bool found = false;

    for(int d = 0; d < NUMDIRE && !found; d++){
        int new_r = r + movr[d], new_c = c + movc[d];
        if(in_range(new_r, new_c) && !used[new_r][new_c]){
            if(_solve(p, i + 1, new_r, new_c))
                found = true;
        }
    }

    used[r][c] = false;
    return found;
}

bool find_word(int p){
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++)
            if(_solve(p, 0, r, c))
                return true;
    }
    return false;
}

int solve(){
    int s = 0;
    for(int i = 0; i < m; i++){
        if(find_word(i))
            s+= score_per_len(word_len[i]);
    }

    return s;
}

//#define cout out
int main(){
    //fstream out;
    //out.open("output.txt", ios::out);

    int T;
    cin >> T;

    for(int t = 0; t < T; t++){
        init();
        cout<<"Score for Boggle game #"<<t + 1<<": "<<solve()<<"\n";
    }
}
