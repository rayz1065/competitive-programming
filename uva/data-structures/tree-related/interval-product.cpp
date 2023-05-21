#include <bits/stdc++.h>
#define MAXN 1000005
#define ST_SIZE (MAXN * 4 + 5)

#define LFT(x) (x << 1)
#define RGT(x) ((x << 1) + 1)

#define NO_CONTRIBUTION 1

using namespace std;

int st[ST_SIZE];
int n, k;

int sign(int value){
    if(value < 0) return -1;
    if(value > 0) return +1;
    return 0;
}

int _update_value(int A, int B, int i, int k, int new_value){
    assert(A <= B);
    if(A == i && B == i)
        return st[k] = sign(new_value);

    if(A > i || B < i)
        return st[k];

    int mid = (A + B)/2;
    return st[k] = _update_value(A, mid, i, LFT(k), new_value) * _update_value(mid + 1, B, i, RGT(k), new_value);
}

void update_value(int i, int new_value){
    _update_value(0, MAXN, i, 1, new_value);
}

int _get_product(int A, int B, int a, int b, int k){
    if(b < A || a > B) return NO_CONTRIBUTION;
    if(a <= A && B <= b)
        return st[k];

    int mid = (A + B)/2;
    return _get_product(A, mid, a, b, LFT(k)) * _get_product(mid + 1, B, a, b, RGT(k));
}

int get_product(int a, int b){
    return _get_product(0, MAXN, a, b, 1);
}

bool init(){
    if(!(cin >> n >> k))
        return false;

    for(int i = 0; i < n; i++){
        int v;
        cin >> v;
        update_value(i, v);
    }

    return true;
}

char sign_char(int v){
    v = sign(v);
    if(v == +1) return '+';
    if(v == -1) return '-';
    return '0';
}

void solve(){
    char c;
    int a, b;
    for(int i = 0; i < k; i++){
        cin >> c >> a >> b;
        if(c == 'C'){
            update_value(a - 1, b);
        }
        else if(c == 'P'){
            cout<<sign_char(get_product(a - 1, b - 1));
        }
    }
    cout<<"\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(init()){
        solve();
    }
}
