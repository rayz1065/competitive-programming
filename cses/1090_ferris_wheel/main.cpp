#include <bits/stdc++.h>
#define MAXN 500001
using namespace std;

int bambini[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, pesomax;
    cin>>N>>pesomax;

    for(int i = 0; i < N; i++)
        cin>>bambini[i];
    sort(bambini, bambini + N);

    int m = 0, S = 0;
    for(int i = N - 1; i >= m; i--){
        if(bambini[m] + bambini[i] <= pesomax)
            m++;
        S++;
    }
    cout<<S;
}
