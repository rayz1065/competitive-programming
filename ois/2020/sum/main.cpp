#include <bits/stdc++.h>
#define MAXN 10005
#define ALF 26

using namespace std;

int n;
string a, b, sol;
bool used[MAXN];

int dig_meaning[30];

bool has_meaning(char c){
    return dig_meaning[c - 'A'] != -1;
}

int get_dig(char c){
    assert(has_meaning(c));
    return dig_meaning[c - 'A'];
}

void set_dig(char c, int v){
    assert(!has_meaning(c) && !used[v]);
    used[v] = true;
    dig_meaning[c - 'A'] = v;
}

void unset_dig(char c){
    assert(has_meaning(c));
    used[dig_meaning[c - 'A']] = false;
    dig_meaning[c - 'A'] = -1;
}

int get_res_dig(int i){
    if(i < 0) return 0;
    return sol[i] - '0';
}

bool solved = false;

void solve(int i, int res_i, int riporto){
    if(solved)
        return ;

    if(i == -1){
        if(get_res_dig(res_i) == riporto){
            for(int k = 0; k < n; k++)
                cout<<get_dig(a[k]);
            cout<<"\n";
            for(int k = 0; k < n; k++)
                cout<<get_dig(b[k]);
            cout<<"\n";
            // found sol
            solved = true;
            return ;
        }
    }

    if(!has_meaning(a[i])){
        for(int v = 0; v <= 9; v++){
            if(!used[v]){
                set_dig(a[i], v);
                solve(i, res_i, riporto);
                unset_dig(a[i]);
            }
        }
        return ;
    }
    if(!has_meaning(b[i])){
        for(int v = 0; v <= 9; v++){
            if(!used[v]){
                set_dig(b[i], v);
                solve(i, res_i, riporto);
                unset_dig(b[i]);
            }
        }
        return ;
    }
    if(n > 1 && i == 0 && (get_dig(a[i]) == 0 || get_dig(b[i]) == 0))
        return ;

    if((riporto + get_dig(a[i]) + get_dig(b[i]))%10 == get_res_dig(res_i))
        solve(i - 1, res_i - 1, (riporto + get_dig(a[i]) + get_dig(b[i]))/10);
}

int main(){
    fill(dig_meaning, dig_meaning + ALF, -1);
    cin >> a >> b >> sol;
    n = a.length();
    solve(n - 1, sol.length() - 1, 0);

    while(!solved);
}
