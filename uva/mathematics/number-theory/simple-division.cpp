#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int N;
int numeri[MAXN];

int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

int main(){
    FILE *out = stdout;
    while(true){
        N = 0;
        while(cin >> numeri[N]){
            if(numeri[N] == 0)
                break ;
            N++;
        }
        if(N == 0)
            break ;

        int G = numeri[1] - numeri[0];
        for(int i = 2; i < N; i++)
            G = gcd(G, numeri[i] - numeri[0]);

        fprintf(out, "%d\n", abs(G));
    }
}
