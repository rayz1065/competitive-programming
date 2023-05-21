#include <bits/stdc++.h>
#define MAXN 200005
#define LAST_BIT(x) (x & (-x))

#ifndef _WIN32
    #define getchar() getchar_unlocked()
#endif // _WIN32

using namespace std;

int fenw[MAXN];
int pot[MAXN];

void fast_in(int &a){
    char c = getchar();
    a = 0;
    while(c < '0') c = getchar();
    while(c >= '0') a = a*10 + c - '0', c = getchar();
}

void update_fenw_tree(int i, int x){
    i++;
    while(i < MAXN)
        fenw[i]+= x, i+= LAST_BIT(i);
}

int get_sum(int i){
    i++;
    int s = 0;
    while(i > 0)
        s+= fenw[i], i-= LAST_BIT(i);
    return s;
}

int sum_range(int a, int b){
    if(a)
        return get_sum(b) - get_sum(a - 1);
    return get_sum(b);
}

void init_fenw_tree(){
    fill(fenw, fenw + MAXN, 0);
}

int n;

bool init(){
    fast_in(n);
    if(!n) return false;

    init_fenw_tree();

    for(int i = 0; i < n; i++){
        fast_in(pot[i]);
        update_fenw_tree(i, pot[i]);
    }

    return true;
}

//fstream out;

void solve(){
    char c;
    c = getchar();
    while(c == '\n') c = getchar();

    while(c != 'E'){
        int a, b;
        fast_in(a), fast_in(b);
        if(c == 'M'){
            a--, b--;
            cout<<sum_range(a, b)<<"\n";
        }
        else{
            a--;
            update_fenw_tree(a, b - pot[a]);
            pot[a] = b;
        }
        c = getchar();
        while(c == '\n') c = getchar();
    }
    while(getchar() != '\n');
}

int main(){
    //out.open("output.txt", ios::out);

    int t = 0;
    while(init()){
        if(t) cout<<"\n";
        cout<<"Case "<<++t<<":\n";
        solve();
    }

}
