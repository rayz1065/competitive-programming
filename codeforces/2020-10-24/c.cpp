#include <bits/stdc++.h>
#define MOD 1000000007
#define MAXN 1005

using namespace std;

int n, x, pos;
int curr[MAXN];
vector<char> steps[MAXN];

bool binarySearch(int x){
    vector<char> currSteps;
    int l = 0, r = n;

    while(l < r){
        int m = (l + r)/2;
        if(curr[m] <= x){
            l = m + 1;
            if(curr[m] == x)
                currSteps.push_back('e');
            else
                currSteps.push_back('l');
        }
        else{
            r = m;
            currSteps.push_back('g');
        }
    }
    assert(l > 0 && curr[l - 1] == x);
    steps[l - 1] = currSteps;
    if(l > 0 && curr[l - 1] == x)
        return true;
    return false;
}

void init(){
    cin >> n >> x >> pos;
    for(int i = 0; i < MAXN; i++)
        curr[i] = i + 1;

    for(int i = 1; i <= n; i++)
        binarySearch(i);

    /*for(int i = 0; i < n; i++){
        cout<<i<<":\t";
        for(auto j:steps[i])
            cout<<j<<" ";
        cout<<"\n";
    }*/
}

/*void printCurr(){
    for(int i = 0; i < n; i++)
        cout<<curr[i]<<" ";
    cout<<" => "<<binarySearch()<<"\n";
}

int solve(){
    int s = 0;
    do{
        if(binarySearch())
            s++;
        printCurr();
    } while(next_permutation(curr, curr + n));
    return s;
}*/

long long int modInverse(long long int a, long long int m){
    long long int m0 = m;
    long long int y = 0, x = 1;

    if (m == 1)
      return 0;

    while (a > 1){
        long long int q = a / m;
        long long int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
       x += m0;

    return x;
}

int lt(int x){
    return x - 1;
}

int et(int x){
    return 1;
}

int gt(int x){
    return n - x;
}

long long int fact(int n){
    long long int s = 1;
    for(int i = 1; i <= n; i++)
        s = (s*i)%MOD;
    return s;
}

long long int bino(int n, int k){
    // cout<<"cnk("<<n<<", "<<k<<"): "<<(fact(n))<<" * "<<(modInverse((fact(k)*fact(n - k))%MOD, MOD))<<"\t"<<(fact(k)*fact(n - k))<<"\n";
    return (fact(n)*modInverse((fact(k)*fact(n - k))%MOD, MOD))%MOD;
}

int solve(){
    int l = 0, e = 0, g = 0;
    for(auto j:steps[pos]){
        if(j == 'l') l++;
        if(j == 'e') e++;
        if(j == 'g') g++;
    }

    //cout<<l<<" "<<e<<" "<<g<<"\n";
    //cout<<lt(x)<<" "<<et(x)<<" "<<gt(x)<<"\n";

    if(l > lt(x)) return 0;
    if(e > et(x)) return 0;
    if(g > gt(x)) return 0;

    //cout<<"lt: "<<bino(lt(x), l)<<"\ngt: "<<bino(gt(x), g)<<"\n";
    return (((((bino(lt(x), l)*bino(gt(x), g))%MOD)*fact(n - l - e - g))%MOD)*((fact(l)*fact(g))%MOD))%MOD;
}

int main(){
    init();

    cout<<solve()<<"\n";
    //cout<<"x = "<<x<<" pos = "<<pos<<" s = "<<solve()<<"\tfact = "<<fact()<<"\n";
}
