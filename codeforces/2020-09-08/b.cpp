#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n;

int a[MAXN];
bool used[MAXN];

vector<int> sol;

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    memset(used, 0, sizeof used);
    sol.clear();
}

int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

int solve(){
    int *m = max_element(a, a + n);
    used[m - a] = true;
    sol.push_back(*m);
    int currGcd = *m;

    for(int it = 0; it < n - 1; it++){
        int currBest = 0, currBestIdx = -1;
        for(int i = 0; i < n; i++){
            if(!used[i]){
                if(gcd(a[i], currGcd) > currBest){
                    currBest = gcd(a[i], currGcd);
                    currBestIdx = i;
                }
            }
        }
        used[currBestIdx] = true;
        currGcd = currBest;
        sol.push_back(a[currBestIdx]);
    }
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();

        for(auto i:sol)
            cout<<i<<" ";
        cout<<"\n";
    }
}
