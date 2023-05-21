// note, this is kept for archival reasons, actual solution is exclusively_edible.cpp

#include <bits/stdc++.h>
#define MAXN 50
using namespace std;
int X, Y;
int memo[MAXN][MAXN][MAXN][MAXN];
bool willWin(int a, int b, int N, int M){ /// non so neanche cosa stavo pensando, per la soluzione "uva exclusivly edible2.cpp"
    if(a==X&&b==Y&&N==X+1&&M==Y+1)
        return false;

    if(memo[a][b][N][M]==0)
        for(int i=a; i<=X; i++)
            for(int j=b; j<=Y; j++)
                for(int h=N; h>X; h--)
                    for(int k=M; k>Y; k--)
                        if(!(i==a&&j==b&&h==N&&k==M)&&!willWin(i, j, h, k))
                            memo[a][b][N][M]=2;

    if(memo[a][b][N][M]==0)
        memo[a][b][N][M]=1;
    //cout<<a<<" "<<b<<" "<<N<<" "<<M<<" ";
    //cout<<memo[a][b][M][M]<<endl;
    return memo[a][b][N][M]-1;
}

int main(){
    int T;
    cin>>T;
    for(int c=0; c<T; c++){
        int N, M;
        cin>>N>>M>>X>>Y;
        for(int i=0; i<MAXN; i++)
            for(int j=0; j<MAXN; j++)
                for(int h=MAXN-1; h>=0; h--)
                    for(int k=MAXN-1; k>=0; k--)
                        memo[i][j][h][k]=0;
        cout<<willWin(0, 0, N, M)<<endl;
    }
}
