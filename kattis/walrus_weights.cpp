#include <bits/stdc++.h>
#define MAXN 1005
#define MAXW 2005

using namespace std;

int weights[MAXN];
bool dp[2][MAXW];

int main() {
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    dp[1][0] = true;
    for(int i = 0; i < n; i++) {
        fill(dp[i%2], dp[i%2] + MAXW, false);
        for(int w = 0; w < MAXW; w++) {
            if(dp[(i + 1)%2][w]) {
                dp[i%2][w] = true;
            }
            if(w - weights[i] >= 0 && dp[(i + 1)%2][w - weights[i]]){
                dp[i%2][w] = true;
            }
        }
    }

    for(int w = 0; w <= 1000; w++){
        if(dp[(n + 1)%2][w + 1000] || dp[(n + 1)%2][1000 - w]){
            int res = w + 1000;
            if(!dp[(n + 1)%2][w + 1000]){
                res = 1000 - w;
            }
            cout<<res<<"\n";
            return 0;
        }
    }
}