#include <bits/stdc++.h>
#ifdef _WIN32
    #define gc() getchar()
#else
    #define gc() getchar_unlocked()
#endif
#define MAXN 5000005
using namespace std;
typedef long long int ulli;

/*void readInt(ulli &N){
    char c;
    N = 0;
    c = gc();
    while(c != '-' && (c < '0' || c > '9'))
        c = gc();
    bool meno = false;
    if(c == '-'){
        meno = true;
        c = gc();
    }
    while(c >= '0' && c <= '9'){
        N = N*10 + c - '0';
        c = gc();
    }
    if(meno)
        N*= -1;
}*/

ulli N, Q;
ulli fenwick[MAXN];

ulli getSum(ulli i){
    ulli S = 0;
    while(i > 0){
        S+= fenwick[i];
        i-= i&((~i) + 1);
    }
    return S;
}

void addVal(ulli i, ulli v){
    while(i < MAXN){
        fenwick[i]+= v;
        i+= i&((~i) + 1);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> Q;

    for(int i = 0; i < Q; i++){
        char op;
        ulli n;
        cin >> op >> n;
        if(op == '?')
            cout<<getSum(n)<<"\n";
        else{
            ulli v;
            cin >> v;
            addVal(n + 1, v);
        }
    }
}
