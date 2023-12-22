#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int n;
long long int a[MAXN];
long long int b[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> b[i];
}

long long int solve(){
    long long int chosena = *min_element(a, a + n);
    long long int chosenb = *min_element(b, b + n);

    long long int s = 0;
    for(int i = 0; i < n; i++){
        long long int toadd = min(a[i] - chosena, b[i] - chosenb);
        s+= toadd + a[i] - chosena + b[i] - chosenb - 2*toadd;
    }
    return s;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
