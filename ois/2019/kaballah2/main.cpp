#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;

int N, M;
int cifre[MAXN][MAXN];
int freq[10000];
int movR[] = {-1, -1, -1, 0, 1, 1, 1, 0}, movC[] = {-1, 0, 1, 1, 1, 0, -1, -1};

typedef pair<int, int> pii;

inline bool inRange(int r, int c){
    return (r >= 0 && c >= 0 && r < N && c < M);
}

void solve(int r, int c){
    if(cifre[r][c] == 0)
        return ;
    for(int m = 0; m < 8; m++){
        int newR = r, newC = c;
        int a = 0;
        for(int dig = 0; dig < 4 && inRange(newR, newC); dig++, newR+= movR[m], newC+= movC[m]){
            a = a*10 + cifre[newR][newC];
        }
        if(a >= 1000 && a < 10000)
            freq[a]++;
    }
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N >> M;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            char c;
            in >> c;
            cifre[i][j] = c - '0';
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            solve(i, j);
        }
    }

    int best = 0;
    for(int i = 1000; i < 10000; i++){
        if(freq[i] > freq[best])
            best = i;
    }
    cout<<best<<" "<<freq[best];
}
