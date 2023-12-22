#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int n;
int curr[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        curr[i] = i + 1;
}

bool is_good_sub(int i, int j){
    int s = 0, chk = j - i + 1;
    for(int a = i; a <= j; a++)
        s|= curr[a];

    return s >= chk;
}

bool is_good(){
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(!is_good_sub(i, j))
                return false;
        }
    }
    return true;
}

void solve(){
    while(!is_good())
        random_shuffle(curr, curr + n); // ?????????????

    for(int i = 0; i < n; i++)
        cout<<curr[i]<<" ";
    cout<<"\n";
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
    }
}
