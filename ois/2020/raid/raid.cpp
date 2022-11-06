#include <bits/stdc++.h>
#pragma GCC optimize ("O3")

#define MAXN 100005
#define MAXP 1000005
#ifndef _WIN32
    #define getchar() getchar_unlocked()
#endif // _WIN32

using namespace std;

int n, p;
int houses[MAXN];
int ordine[MAXN];

int destr_time[MAXN];

void read_int(int &n){
    n = 0;
    char c = getchar();
    while(c < '0') c = getchar();
    while(c >= '0')
        n = n * 10 + c - '0', c = getchar();
}

bool comp(int i, int j){
    return houses[i] > houses[j];
}

void init(){
    read_int(n), read_int(p);
    houses[0] = houses[n + 1] = -1;
    for(int i = 1; i <= n; i++)
        read_int(houses[i]), ordine[i - 1] = i;
    sort(ordine, ordine + n, comp);
}

int solve(){
    for(int i = 0; i < n; i++){
        int c = ordine[i];
        if(houses[c] > houses[c + 1] && houses[c] > houses[c - 1])
            destr_time[c] = max(destr_time[c + 1], destr_time[c - 1]) + 1, houses[c] = 0;
        else
            destr_time[c] = MAXP;
    }

    int s = 0;
    for(int i = 1; i <= n; i++)
        if(destr_time[i] <= p)
            s++;
    return s;
}

int main(){
    init();
    cout<<solve()<<"\n";
}
