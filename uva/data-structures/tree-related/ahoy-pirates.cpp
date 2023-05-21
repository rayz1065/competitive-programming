#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#define MAXN (1<<20) - 1

#define ST_SIZE (((1<<20) << 1) + 5)
#define ROOT_NODE 0
#define CHILD_NODE(k, j) ((k<<1) + j)
#define LEAF_POS(x) MAXN + x
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

void propagate(int dim, int k){
    Tmut lazy = st[k].lazy;
    st[k].lazy = EMPTY;

    if(lazy == F_MUT)
        st[k].sum = dim;
    else if(lazy == E_MUT)
        st[k].sum = 0;
    else if(lazy == I_MUT)
        st[k].sum = dim - st[k].sum;

    if(dim > 1){
        // propagation
        apply_lazy_value(LFT(k), lazy);
        apply_lazy_value(RGT(k), lazy);
    }
}

int a, b;
Tmut op;

int _update_st(int A, int B, int k){
    if(A > b || B < a){
        if(st[k].lazy)
            propagate(B - A + 1, k);
        return st[k].sum;
    }
    if(a <= A && B <= b){
        apply_lazy_value(k, op);

        if(st[k].lazy)
            propagate(B - A + 1, k);
        return st[k].sum;
    }

    if(st[k].lazy)
        propagate(B - A + 1, k);

    int mid = (A + B) >> 1;
    return st[k].sum = _update_st(A,       mid, LFT(k)) +
                       _update_st(mid + 1, B,   RGT(k));
}

int _count_bucanneer(int A, int B, int k){
    if(A > b || B < a) return 0;
    if(a <= A && B <= b){
        if(st[k].lazy)
            propagate(B - A + 1, k);
        return st[k].sum;
    }

    if(st[k].lazy)
        propagate(B - A + 1, k);

    int mid = (A + B) >> 1;
    return _count_bucanneer(A, mid, LFT(k)) + _count_bucanneer(mid + 1, B, RGT(k));
}

void init_st_tree(){
    int x = LEAF_POS(0);
    while(x--)
        st[x].sum = st[LFT(x)].sum + st[RGT(x)].sum;
}

int n, k;

void update_st(int _a, int _b, Tmut _op){
    a = _a, b = _b, op = _op;
    _update_st(0, MAXN, ROOT_NODE);
}

int count_buccaneer(int _a, int _b){
    a = _a, b = _b;
    return _count_bucanneer(0, MAXN, ROOT_NODE);
}

inline Tmut from_pirate(int pirate){
    return (pirate) ? F_MUT : E_MUT;
}

inline Tmut from_char(char c){
    if(c == 'F') return F_MUT;
    if(c == 'E') return E_MUT;
    if(c == 'I') return I_MUT;
    assert(false);
}

void init(){
    for(int i = 0; i < ST_SIZE; i++) st[i].sum = 0, st[i].lazy = EMPTY;
    int d;
    cin >> d;

    n = 0;

    while(d--){
        int t;
        string pirates;

        cin >> t >> pirates;
        while(t--){
            for(int i = 0; i < pirates.length(); i++)
                st[LEAF_POS(n++)].sum = pirates[i] - '0'; //update_st(n, n, from_pirate(pirates[i] - '0')), n++;
        }
    }
    init_st_tree();
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
