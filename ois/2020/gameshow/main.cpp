#include <bits/stdc++.h>
#define MAXN 100005

#pragma GCC optimize ("O3")

#ifndef _WIN32
    #define getchar() getchar_unlocked()
#endif // _WIN32

using namespace std;

int n, m;
int p[MAXN], c[MAXN];

void read_int(int &n){
    n = 0;
    char c = getchar();
    while(c < '0') c = getchar();
    while(c >= '0')
        n = n * 10 + c - '0', c = getchar();
}

void init(){
    read_int(n), read_int(m);

    for(int i = 0; i < n; i++)
        read_int(p[i]);
    for(int i = 0; i < n; i++)
        read_int(c[i]);
}

void solve(){
    int prices = 0;
    for(int i = 0; i < n; i++){
        if(p[i] <= m)
            prices++, m-= p[i];
        else
            m+= c[i];
    }

    cout<<prices<<" "<<m<<"\n";
}

int main(){
    init();
    solve();
}
