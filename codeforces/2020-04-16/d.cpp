#include <bits/stdc++.h>
#define MAXN 10005
#define PREC(x, n) (x + n - 1)%n
using namespace std;

int n;
long long l, r;

vector<int> s;
bool used[MAXN][MAXN];

bool findPath(int node){
    s.push_back(node);
    if(s.size() == (n * (n - 1) + 1))
        return true;

    for(int i = 0; i < n; i++){
        if(!used[node][i]){
            used[node][i] = true;
            if(findPath(i))
                return true;
            used[node][i] = false;
        }
    }
    s.pop_back();
    return false;
}

void solve(){
    for(int i = 0; i < n; i++)
        used[i][i] = true;

    findPath(0);
    for(auto i:s)
        cout<<(i + 1)<<" ";
    cout<<"\n";
}

void init(){
    cin >> n >> l >> r;
    memset(used, 0, sizeof used);
    s.clear();
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
    }
}
