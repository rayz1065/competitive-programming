#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n;
int x;

int part[MAXN];

void init(){
    cin >> n >> x;
    for(int i = 0; i < n; i++)
        cin >> part[i];
}

int infectedCount(){
    int s = 0;
    for(int i = 0; i < n; i++)
        if(part[i] == x)
            s++;
    return s;
}

int solve(){
    int infected = infectedCount();
    if(infected == n) return 0;
    if(infected) return 1;

    int s = 0;
    for(int i = 0; i < n; i++)
        s+= part[i] - x;

    if(s == 0) return 1;

    return 2;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
