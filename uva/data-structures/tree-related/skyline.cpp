#include <bits/stdc++.h>
#define MAXN 100005

#define ST_SIZE ((1 << 18) + 5)
#define ROOT_NODE 0
#define CHILD_NODE(k, j) ((k<<1) + j + 1 - ROOT_NODE)
#define LFT(k) CHILD_NODE(k, 0)
#define RGT(k) CHILD_NODE(k, 1)

using namespace std;

struct st_node{
    int l_height;
    int lazy;
} st[ST_SIZE];

int tot_overlap;

void propagate(int A, int B, int k){
    if(!st[k].lazy) return ;

    int lazy = st[k].lazy;
    st[k].lazy = 0;

    if(st[k].l_height > lazy) return ;
    st[k].l_height = lazy;

    if(A == B){
        tot_overlap++;
    }
    else{
        int mid = (A + B) >> 1;
        if(st[LFT(k)].lazy) propagate(A, mid, LFT(k));
        if(st[RGT(k)].lazy) propagate(mid + 1, B, RGT(k));

        st[LFT(k)].lazy = lazy;
        st[RGT(k)].lazy = lazy;
    }
}

int _update_st(int a, int b, int A, int B, int k, int h){
    propagate(A, B, k);

    if(B < a || A > b) return st[k].l_height;
    // if(st[k].l_height > h) return st[k].l_height;
    if(a <= A && B <= b){
        st[k].lazy = h;
        propagate(A, B, k);
        return st[k].l_height;
    }

    int mid = (A + B)>>1;
    return st[k].l_height = min(_update_st(a, b, A, mid, LFT(k), h), _update_st(a, b, mid + 1, B, RGT(k), h));
}

void propagate_all(int A, int B, int k){
    propagate(A, B, k);
    if(A == B) return ;

    int mid = (A + B)>>1;
    propagate_all(A, mid, LFT(k));
    propagate_all(mid + 1, B, RGT(k));
}

void update_st(int a, int b, int h){
    _update_st(a, b, 0, MAXN, ROOT_NODE, h);
}

int q;

void init(){
    cin >> q;
    tot_overlap = 0;
    for(int i = 0; i < ST_SIZE; i++)
        st[i] = {0, 0};

    for(int i = 0; i < q; i++){
        int l, r, h;
        cin >> l >> r >> h;
        r--;
        update_st(l, r, h);
    }
}

int solve(){
    propagate_all(0, MAXN, ROOT_NODE);
    return tot_overlap;
}

int main(){
    //fstream out;
    //out.open("output.txt", ios::out);
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    while(n--){
        init();
        cout<<solve()<<"\n";
    }
    getchar();
    getchar();
}
