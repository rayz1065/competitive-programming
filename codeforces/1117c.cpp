#include <bits/stdc++.h>
#define MAXN 100005
#define MOLTO 10000000
using namespace std;

enum {UP, DWN, LFT, RGHT};
int movX[] = {0, 0, -1, +1}, movY[] = {+1, -1, 0, 0};
char S[MAXN];

char moves[] = "UDLR";

int main(){
    long long x, y, x2, y2, xBeg, yBeg;
    cin >> x >> y >> x2 >> y2;

    x-= x2, y-= y2;

    int N;
    cin >> N;

    cin >> S;

    xBeg = x, yBeg = y;

    int minDist = abs(x) + abs(y), tMinDist = 0;

    for(int i = 0; i < N; i++){
        int mov = 0;
        while(mov < 3 && moves[mov] != S[i%N])
            mov++;
        x+= movX[mov], y+= movY[mov];

        if(abs(x) + abs(y) <= i + 1){
            cout<<i + 1<<"\n";
            return 0;
        }

        if(abs(x) + abs(y) - i - 1 < minDist)
            minDist = abs(x) + abs(y) - i - 1, tMinDist = i;
    }

    if(minDist == abs(xBeg) + abs(yBeg)){
        cout<<-1<<"\n";
        return 0;
    }

    int deltaDist = (abs(xBeg) + abs(yBeg)) - (abs(x) + abs(y) - (N));
    for(int nLoops = 1; minDist - nLoops*deltaDist > 0; nLoops++){}

    cout<<tMinDist<<"\t=>\t"<<minDist<<", "<<deltaDist<<"\n";
}
