#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int N;
long long M;

int kids[MAXN];

long long get_sum(){
    long long s = 0;
    for(int i = 0; i < N; i++)
        s+= kids[i];
    return s;
}

int solve(){
    if(M == 0) return N - 1;

    int k = -1;

    while(k < N && M > 0){
        M-= kids[++k];
    }

    return k;
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;
    for(int i = 0; i < N; i++)
        cin >> kids[i];

    M %= get_sum();

    cout<<solve()<<"\n";
}
