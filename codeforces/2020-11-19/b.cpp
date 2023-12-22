#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

typedef long long int lli;

int n;
lli a[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
}

lli solve(){
    sort(a, a + n);

    lli sum = 0;
    for(int i = 0; i < n; i++)
        sum+= a[i];

    lli greatest = a[n - 1];
    /*lli currSnmu = sum - greatest;
    lli snmu = greatest * (n - 2);


    return max(mod, snmu - currSnmu);*/

    lli ifAllGreatest = greatest*(n - 1);

    lli mod = sum%(n - 1);
    if(ifAllGreatest < sum)
        return mod;
    return ifAllGreatest - sum;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
