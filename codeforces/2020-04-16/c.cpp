#include <bits/stdc++.h>
#define MAXN 300005
#define PREC(x, n) (x + n - 1)%n
using namespace std;

int n;
long long h[MAXN];
long long b[MAXN];
long long toKill[20][MAXN];

long long startAt(int i){
    long long s = h[i];
    int j = (i + 1)%n;
    int k = 20;
    int rem = n - 1;

    while(rem > 0){
        k--;
        // assert(k >= 0 && 0 <= j && j < n);

        if((1<<k) <= rem){
            s+= toKill[k][j];
            rem-= (1<<k);
            j = (j + (1<<k))%n;
        }
    }

    return s;
}

long long solve(){
    long long s = LLONG_MAX;

    for(int i = 0; i < n; i++)
        toKill[0][i] = max(0ll, h[i] - b[PREC(i, n)]);

    for(int k = 1; (1<<k) < n; k++){
        for(int i = 0; i < n; i++){
            /// prec was killed, we want to kill 2^k monsters
            toKill[k][i] = toKill[k - 1][i] +
                           toKill[k - 1][(i + (1<<(k - 1)))%n];
        }
    }

    for(int i = 0; i < n; i++)
        s = min(s, startAt(i));

    return s;
}

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> h[i] >> b[i];
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
