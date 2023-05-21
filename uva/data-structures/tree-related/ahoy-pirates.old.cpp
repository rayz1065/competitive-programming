#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#define MAXN 1024005

#define ST_SIZE ((MAXN << 2) + 5)
#define ROOT_NODE 0
#define CHILD_NODE(k, j) ((k<<1) + j)
#define LFT(k) CHILD_NODE(k, 1)
#define RGT(k) CHILD_NODE(k, 2)

using namespace std;

typedef enum {EMPTY, F_MUT, E_MUT, I_MUT} Tmut;

struct st_node{
    Tmut lazy;
    int sum;
};

st_node st[ST_SIZE];

void apply_lazy_value(int k, Tmut lazy){
    if(!st[k].lazy || lazy == F_MUT || lazy == E_MUT) st[k].lazy = lazy;

    else if(lazy == I_MUT){
        if(st[k].lazy == F_MUT) st[k].lazy = E_MUT;
        else if(st[k].lazy == E_MUT) st[k].lazy = F_MUT;
        else st[k].lazy = EMPTY;
    }
}
void propagate(int A, int B, int k){
    if(!st[k].lazy) return;

    Tmut lazy = st[k].lazy;
    st[k].lazy = EMPTY;

    if(lazy == F_MUT)
        st[k].sum = B - A + 1;
    else if(lazy == E_MUT)
        st[k].sum = 0;
    else if(lazy == I_MUT)
        st[k].sum = (B - A + 1) - st[k].sum;

    if(A != B){
        // propagation
        apply_lazy_value(LFT(k), lazy);
        apply_lazy_value(RGT(k), lazy);
    }
}

int a, b;
Tmut op;

int _update_st(int a, int b, int A, int B, int k, Tmut op){
    if(A > b || B < a){
        propagate(A, B, k);
        return st[k].sum;
    }
    if(a <= A && B <= b){
        apply_lazy_value(k, op);
        propagate(A, B, k);
        return st[k].sum;
    }

    propagate(A, B, k);
    int mid = (A + B) >> 1;
    return st[k].sum = _update_st(a, b, A,       mid, LFT(k), op) +
                       _update_st(a, b, mid + 1, B,   RGT(k), op);
}
int _count_bucanneer(int a, int b, int A, int B, int k){
    if(A > b || B < a) return 0;
    if(a <= A && B <= b){
        propagate(A, B, k);
        return st[k].sum;
    }

    propagate(A, B, k);
    int mid = (A + B) >> 1;
    return _count_bucanneer(a, b, A, mid, LFT(k)) + _count_bucanneer(a, b, mid + 1, B, RGT(k));
}

void update_st(int a, int b, Tmut op){
    _update_st(a, b, 0, MAXN, ROOT_NODE, op);
}

int count_buccaneer(int a, int b){
    return _count_bucanneer(a, b, 0, MAXN, ROOT_NODE);
}

Tmut from_pirate(int pirate){
    //assert(pirate == 0 || pirate == 1);
    // 0 -> barbary, 1 -> bucanneer
    return (pirate) ? F_MUT : E_MUT;
}

Tmut from_char(char c){
    if(c == 'F') return F_MUT;
    if(c == 'E') return E_MUT;
    if(c == 'I') return I_MUT;
    assert(false);
}

int n, k;

void init(){
    int d;
    cin >> d;

    n = 0;

    while(d--){
        int t;
        string pirates;

        cin >> t >> pirates;
        while(t--){
            for(int i = 0; i < pirates.length(); i++)
                update_st(n, n, from_pirate(pirates[i] - '0')), n++;
        }
    }
    cin >> k;
}

//fstream out;

void solve(){
    int q = 0;

    while(k--){
        char op;
        int a, b;
        cin >> op >> a >> b;

        if(op == 'S'){
            cout<<"Q"<<++q<<": "<<count_buccaneer(a, b)<<"\n";
        }
        else{
            update_st(a, b, from_char(op));
        }
    }
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    //out.open("output.txt", ios::out);

    int T;
    cin >> T;

    for(int t = 1; t <= T; t++){
        init();
        cout<<"Case "<<t<<":\n";
        solve();
    }
}
