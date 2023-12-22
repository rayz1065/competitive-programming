#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int numeri[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> numeri[i];
}

void solve(){
    int mi = INT_MAX/2, ma = INT_MIN/2;

    int muc = 0;
    for(int i = 0; i < n; i++)
        if(numeri[i] == -1)
            muc++;

    int m, k;
    if(muc == n)
        m = 0, k = 42;
    else{
        if(muc != 0){
            for(int i = 0; i < n; i++){
                if(numeri[i] == -1) continue;
                if(i > 0 && numeri[i - 1] == -1)
                    mi = min(mi, numeri[i]), ma = max(ma, numeri[i]);
                else if(i + 1 < n && numeri[i + 1] == -1)
                    mi = min(mi, numeri[i]), ma = max(ma, numeri[i]);
            }

            k = (mi + ma)/2;
        }
        else
            k = 42;

        m = 0;

        for(int i = 0; i < n; i++)
            if(numeri[i] == -1) numeri[i] = k;

        for(int i = 0; i < n; i++){
            if(i > 0)
                m = max(m, abs(numeri[i] - numeri[i - 1]));
            if(i + 1 < n)
                m = max(m, abs(numeri[i] - numeri[i + 1]));
        }
    }
    cout<<m<<" "<<k<<"\n";
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
    }
}
