#include <bits/stdc++.h>
#ifdef _WIN32
    #define getchar_unlocked getchar
#endif // _WIN32
#define MAXN 1005
using namespace std;

int N;
char tavole[MAXN][MAXN];
int ending[MAXN];

int getNext(char t, int r, int i){
    while(i < N && tavole[r][i] != t)
        i++;
    return i;
}

int getScore(char team, char otherTeam){
    int maxS = 0;
    for(int i = 0; i < N; i++){
        int curr = 0;
        for(int r = 0; r < N; r++){
            if(tavole[r][i] == team){
                if(i == 0 || tavole[r][i - 1] == otherTeam)
                    ending[getNext(otherTeam, r, i)]++;
                curr++;
            }
        }
        for(int j = i; j < N && (N - i)*curr > maxS; j++){
            maxS = max(maxS, (j - i + 1)*curr);
            curr-= ending[j + 1];
        }
    }
    return maxS;
}

void gc(char &c){
    c = getchar();
    if(c != 'R' && c != 'A')
        c = getchar_unlocked();
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            gc(tavole[i][j]);
        }
    }

    int maxF = getScore('R', 'A');
    fill(ending, ending + MAXN, 0);
    int maxW = getScore('A', 'R');

    if(maxF == maxW)
        cout<<0<<" "<<maxF<<endl;
    else if(maxF > maxW)
        cout<<1<<" "<<maxF<<endl;
    else
        cout<<2<<" "<<maxW<<endl;
}
