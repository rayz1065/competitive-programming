#include <bits/stdc++.h>
#define MAXN 101
#define MAXL 1001
#define MOD 1000000007
using namespace std;

int R, C;
char grid[MAXN][MAXN];
int memo[MAXN][MAXN][MAXL];
int movR[] = {-1, -1, -1, 0, 1, 1, 1, 0}, movC[] = {-1, 0, 1, 1, 1, 0, -1, -1};
string word;

int calcola(int r, int c, int idx){
    if(idx == word.size()) return 1;

    if(memo[r][c][idx] == 0){
        int S = 0;

        for(int i=0; i<8; i++)
            if(r<R && r>=0 && c<C && c>=0 && grid[r+movR[i]][c+movC[i]] == word[idx])
                S = (S + calcola(r+movR[i], c+movC[i], idx+1))%MOD;

        memo[r][c][idx] = S + 1;
    }

    return memo[r][c][idx] - 1;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in>>word>>R>>C;

    for(int r=0; r<R; r++)
        for(int c=0; c<C; c++)
            in>>grid[r][c];

    int S = 0;
    for(int r=0; r<R; r++)
        for(int c=0; c<C; c++)
            if(grid[r][c] == word[0])
                S = (S + calcola(r, c, 1))%MOD;
    cout<<S;
}
