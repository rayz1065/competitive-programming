#include <bits/stdc++.h>
#define MAXN 1000005
#define ST_NODES (MAXN<<2)
#define ST_ROOT 0
#define LFT(x) ((x<<1) + 1)
#define RGT(x) ((x<<1) + 2)
using namespace std;

int n, d, p, q;

int root = 0;
int post_id[MAXN];
int padre[MAXN];
vector<int> grafo[MAXN];
pair<int, int> intervallo[MAXN];

int curr_post_id = 0;

enum lazyT{EMPTY, UNSUB, SUB};

struct st_node{
    lazyT lazy;
    int v;
} st[ST_NODES];

void lazy_propagation(int k, int A, int B){
    if(!st[k].lazy) return ;

    lazyT lazy = st[k].lazy;
    st[k].lazy = EMPTY;

    if(lazy == UNSUB) st[k].v = 0;
    if(lazy == SUB) st[k].v = B - A + 1;

    if(A != B){
        st[LFT(k)].lazy = lazy;
        st[RGT(k)].lazy = lazy;
    }
}

int _update_st(int A, int B, int a, int b, int k, lazyT op){
    if(A > b || B < a){
        lazy_propagation(k, A, B);
        return st[k].v;
    }
    if(a <= A && B <= b){
        st[k].lazy = op;
        lazy_propagation(k, A, B);
        return st[k].v;
    }

    lazy_propagation(k, A, B);
    int mid = (A + B) >> 1;
    return st[k].v = _update_st(A, mid, a, b, LFT(k), op) + _update_st(mid + 1, B, a, b, RGT(k), op);
}

int _count_subs(int A, int B, int a, int b, int k){
    if(A > b || B < a) return 0;

    lazy_propagation(k, A, B);
    if(a <= A && B <= b)
        return st[k].v;

    int mid = (A + B) >> 1;
    return _count_subs(A, mid, a, b, LFT(k)) + _count_subs(mid + 1, B, a, b, RGT(k));
}

int count_subs(int a, int b){
    return _count_subs(0, MAXN, a, b, ST_ROOT);
}

int update_st(int a, int b, int op){
    _update_st(0, MAXN, a, b, ST_ROOT, (op == 1) ? SUB : UNSUB);
}

int get_post_id(int nodo){
    if(post_id[nodo] == -1)
        return post_id[nodo] = curr_post_id++;
    return post_id[nodo];
}

pair<int, int> dfs(int nodo){
    if(grafo[nodo].size() == 0)
        return intervallo[nodo] = {get_post_id(nodo), get_post_id(nodo)};

    int mi = INT_MAX >> 1, ma = -1;
    for(auto i:grafo[nodo]){
        pair<int, int> res = dfs(i);
        mi = min(mi, res.first), ma = max(ma, res.second);
    }
    return intervallo[nodo] = {mi, ma};
}

void init(){
    cin >> d >> p >> q;
    n = d + p;
    memset(post_id, (1<<8) - 1, sizeof(post_id));

    for(int i = 0; i < n; i++){
        cin >> padre[i];
        if(padre[i] != -1)
            grafo[padre[i]].push_back(i);
        else
            root = i;
    }

    dfs(root);
}

void solve(){
    for(int i = 0; i < q; i++){
        int op, t;
        cin >> op >> t;
        if(op == 0 || op == 1)
            update_st(intervallo[t].first, intervallo[t].second, op);
        else
            cout<<count_subs(get_post_id(t), get_post_id(t))<<"\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();
    solve();
}
