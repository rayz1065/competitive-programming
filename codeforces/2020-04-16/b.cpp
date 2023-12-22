#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
long long x;
long long mon[MAXN];

int solve(){
    sort(mon, mon + n, greater<int>());

    long long sumM = 0;
    for(int i = 0; i < n; i++){
        sumM+= mon[i];
        if(sumM/(i + 1) < x)
            return i;
    }
    return n;
}

void init(){
    cin >> n >> x;
    for(int i = 0; i < n; i++)
        cin >> mon[i];
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
