#include <bits/stdc++.h>
#define MAXN 2005
#define MAXC 2005
using namespace std;

typedef long long int ulli;

ulli value[MAXN], weight[MAXN];
ulli memo[MAXN][MAXC];
int N;
double C;
stack<int> sol;

void solve(){
    for(int p = 0; (double)p <= C; p++)
        memo[0][p] = 0;
    for(int i = 0; i < N; i++)
        memo[i][0] = 0;

    for(int i = 1; i <= N; i++){
        for(int p = 1; (double)p <= C; p++){
            if(p - weight[i - 1] >= 0){
                memo[i][p] = max(memo[i - 1][p], memo[i - 1][p - weight[i - 1]] + value[i - 1]);
            }
            else
                memo[i][p] = memo[i - 1][p];
        }
    }
    /*for(int i = 0; i <= N; i++){
        for(int p = 0; (double)p <= C; p++)
            cout<<memo[i][p]<<" ";
        cout<<endl;
    }*/
}

void traverse(){
    int i = N, p = C;
    while(i > 0 && p > 0){
        if(p - weight[i - 1] >= 0){
            if(memo[i - 1][p - weight[i - 1]] + value[i - 1] > memo[i - 1][p]){
                sol.push(i - 1);
                p-= weight[i - 1];
            }
        }
        i--;
    }
}

int main(){
    while(cin >> C >> N){
        for(int i = 0; i < N; i++)
            cin >> value[i] >> weight[i];
        solve();
        traverse();

        cout<<sol.size()<<endl;
        while(!sol.empty()){
            cout<<sol.top()<<" ";
            sol.pop();
        }
        cout<<endl;
    }
}
