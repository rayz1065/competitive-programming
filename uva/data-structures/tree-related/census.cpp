#include <bits/stdc++.h>

#define MAXN 505
#define MAXB (MAXN*MAXN + 5)

#define ST_NODES ((MAXB<<2) + 5)
#define ROOT_NODE 0
#define CHILD_NODE(k, j) ((k<<2) + j + 1)

using namespace std;

struct st_node{
    int M;
    int m;
} st[ST_NODES];

st_node st_node_cmb(st_node a, st_node b){
    return {max(a.M, b.M), min(a.m, b.m)};
}

st_node _update_st(int u, int d, int l, int r, int U, int D, int L, int R, int k, int v){
    if(u <= U && D <= d && l <= L && R <= r){
        // u == d && l == r
        //cout<<u<<" <= "<<U<<" && "<<D<<" <= "<<d<<" && "<<l<<" <= "<<L<<" && "<<R<<" <= "<<r<<"\n";
        //cout<<"found it\n";
        return st[k] = {v, v};
    }
    if(L > r || R < l || U > d || D < u){
        return st[k];
    }
    //cout<<k<<":\tU = "<<U<<"\tD = "<<D<<"\tL = "<<L<<"\tR = "<<R<<"\n";

    int UDM = (U + D)/2;
    int LRM = (L + R)/2;

    return st[k] = st_node_cmb(st_node_cmb(_update_st(u, d, l, r, U, UDM, L, LRM, CHILD_NODE(k, 0), v),
                                           _update_st(u, d, l, r, U, UDM, LRM + 1, R, CHILD_NODE(k, 1), v)),
                               st_node_cmb(_update_st(u, d, l, r, UDM + 1, D, L, LRM, CHILD_NODE(k, 2), v),
                                           _update_st(u, d, l, r, UDM + 1, D, LRM + 1, R, CHILD_NODE(k, 3), v)));
}
st_node _search_st(int u, int d, int l, int r, int U, int D, int L, int R, int k){
    if(u <= U && D <= d && l <= L && R <= r){
        //cout<<u<<" <= "<<U<<" && "<<D<<" <= "<<d<<" && "<<l<<" <= "<<L<<" && "<<R<<" <= "<<r<<"\n";
        //cout<<"found it\n";
        return st[k];
    }
    if(L > r || R < l || U > d || D < u){
        return {INT_MIN, INT_MAX};
    }
    //cout<<k<<":\tU = "<<U<<"\tD = "<<D<<"\tL = "<<L<<"\tR = "<<R<<"\n";

    int UDM = (U + D)/2;
    int LRM = (L + R)/2;

    return st_node_cmb(st_node_cmb(_search_st(u, d, l, r, U, UDM, L, LRM, CHILD_NODE(k, 0)),
                                   _search_st(u, d, l, r, U, UDM, LRM + 1, R, CHILD_NODE(k, 1))),
                       st_node_cmb(_search_st(u, d, l, r, UDM + 1, D, L, LRM, CHILD_NODE(k, 2)),
                                   _search_st(u, d, l, r, UDM + 1, D, LRM + 1, R, CHILD_NODE(k, 3))));
}
void update_st(int u, int d, int l, int r, int v){
    _update_st(u, d, l, r, 0, MAXN, 0, MAXN, ROOT_NODE, v);
}
st_node search_st(int u, int d, int l, int r){
    return _search_st(u, d, l, r, 0, MAXN, 0, MAXN, ROOT_NODE);
}

int n, q;

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            int v;
            cin >> v;
            update_st(j, j, i, i, v);
        }

    cin >> q;
}

void solve(){
    for(int i = 0; i < q; i++){
        char o;
        cin >> o;
        if(o == 'q'){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--, y1--, x2--, y2--;
            st_node res = search_st(y1, y2, x1, x2);
            cout<<res.M<<" "<<res.m<<"\n";
        }
        if(o == 'c'){
            int x, y, v;
            cin >> x >> y >> v;
            x--, y--;
            update_st(y, y, x, x, v);
        }
    }
}

int main(){
    init();
    solve();
}
