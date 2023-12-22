#include <bits/stdc++.h>

using namespace std;

/*int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

long long int mcm(int a, int b){
    return (long long int)a*b/gcd(a, b);
}

int solve(int n){
    int s = 1;
    for(int i = 2; i < n; i++){
        if(mcm(i, n - i ) < mcm(s, n - s))
            s = i;
    }
    return s;
}*/

int first_div(int n){
    for(int i = 2; i*i <= n; i++){
        if(n%i == 0)
            return n/i;
    }
    return 1;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;
        int s = first_div(n);
        cout<<s<<" "<<n - s<<"\n";
    }
}
