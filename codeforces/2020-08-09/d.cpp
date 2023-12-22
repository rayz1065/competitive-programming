#include <bits/stdc++.h>
#define MAXN 1000000

using namespace std;

int n, m;
bool curr[5][MAXN];
char line[MAXN];

bool init(){
    cin >> n >> m;
    if(n > 3 && m > 3){
        for(int i = 0; i < n; i++)
            cin >> line;
        return false;
    }
    if(n > m) swap(n, m);

    for(int i = 0; i < n; i++){
        cin >> line;
        for(int j = 0; j < m; j++)
            curr[i][j] = line[j] == '1';
    }
    return true;
}

bool is_good_sqr(int r, int c, int side){
    assert(r + side <= n && c + side <= m);

    int s = 0;

    for(int i = r; i < r + side; i++){
        for(int j = c; j < c + side; j++){
            s+= curr[i][j];
        }
    }

    //cout<<s<<" ";

    return s%2;
}

bool is_good(){
    for(int r = 0; r < n; r++){
        for(int c = 0; c < m; c++){
            for(int side = 2; r + side <= n && c + side <= m; side+= 2){
                if(!is_good_sqr(r, c, side)) return false;
            }
        }
    }
    return true;
}

int solve(int r, int c){
    if(c == m) r++, c = 0;
    if(r == n){
        if(is_good()){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++)
                    cout<<curr[i][j]<<" ";
                cout<<"\n";
            }
            cout<<"\n";
            return 1;
        }
        return 0;
    }

    int s = 0;
    curr[r][c] = false;
    s+= solve(r, c + 1);
    curr[r][c] = true;
    s+= solve(r, c + 1);
    return s;
}

int solve(){
    if(n > 3) return -1;
    return solve(0, 0);
}

int main(){
    init();
    cout<<solve()<<"\n";
}
