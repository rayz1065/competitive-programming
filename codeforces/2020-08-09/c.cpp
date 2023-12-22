#include <bits/stdc++.h>
// #define MAXN 105
#define MOD 1000000007

using namespace std;

int n;
//int curr[MAXN];

unsigned long long int factmod(){
    unsigned long long int s = 1;
    for(int i = 2; i <= n; i++)
        s = (s * i) % (MOD);
    return s;
}

unsigned long long int powmod(){
    unsigned long long int s = 1;
    for(int i = 1; i < n; i++)
        s = (s * 2) % MOD;
    return s;
}

void init(){
    cin >> n;
}

/*bool is_cyclic(){
    int grtleft = curr[0];

    for(int i = 1; i < n; i++){
        if(grtleft > curr[i]){
            for(int j = i + 1; j < n; j++)
                if(curr[i] < curr[j])
                    return true;
        }
        else
            grtleft = curr[i];
    }

    return false;
}*/

int solve(){
    return (factmod() - powmod() + MOD)%MOD;
    /*int s = 0;

    do{
        if(!is_cyclic()){
            s++;
        }
    } while(next_permutation(curr, curr + n));

    cout<<s<<" "<<powmod()<<"\n";
    return factmod() - s;*/
}

int main(){
    init();
    cout<<solve()<<"\n";
}
