#include <bits/stdc++.h>
#define MAXN 200005
#define MAXM 200005

using namespace std;

int n, m;
int curr_debt[MAXN];

int main(){
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        curr_debt[b]+= w;
        curr_debt[a]-= w;
    }

    int pivot = 0, c = 0;
    for(int i = 1; i < n; i++){
        if(curr_debt[i] != 0)
            c++;
    }

    cout<<c<<"\n";
    for(int i = 1; i < n; i++){
        if(curr_debt[i] < 0)
            cout<<pivot<<" "<<i<<" "<<-curr_debt[i]<<"\n";
        if(curr_debt[i] > 0)
            cout<<i<<" "<<pivot<<" "<<curr_debt[i]<<"\n";
    }
}
