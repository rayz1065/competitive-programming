#include <bits/stdc++.h>
#define MAXN 100005
#define INF (1ll<<50)

using namespace std;

typedef long long int lli;

int n, d;
struct antenna{
    lli l; // treshold
    lli p; // power
    lli s; // start time
    lli t; // time interval

    void print(){
        cout<<l<<","<<p<<"\n";
    }

    lli nextt(lli currt){
        currt-= s;
        if(currt < 0)
            return s;
        return (currt/t + 1) * t + s;
    }
} antenne[MAXN];

/*struct stnode{
    ll v = INT_MIN;
    ll lazy = INT_MIN;
} st[MAXN<<2];;

#define ST_ROOT 0
#define LFT(x) ((x<<1) + 1)
#define RGT(x) ((x<<1) + 2)

void assign_lazy(int k, int v){
    if(st[k].v < v && st[k].lazy < v)
        st[k].lazy = v;
}

void propagate(int A, int B, int k){
    if(!st[k].lazy) return;

    ll lazy = st[k].lazy;
    st[k].lazy = INT_MIN;

    st[k].v = max(st[k].v, lazy);

    if(A != B){
        assign_lazy(LFT(k), lazy);
        assign_lazy(RGT(k), lazy);
    }
}

ll _update_st(int A, int B, int a, int b, int k, int v){
    propagate(A, B, k);

    if(A > b || B < a) return st[k].v;
    if(a <= A && B <= b){
        assign_lazy(k, v);
        propagate(A, B, k);
        return st[k].v;
    }

    int mid = (A + B) >> 1;
    st[k].v =
}

void update_st(int a, int b, int v){
    _update_st()
}*/

lli timet[MAXN];
int ordine[MAXN];

bool antennasort(int i, int j){
    return antenne[i].l < antenne[j].l;
}

lli solve(){
    fill(timet, timet + n, INF);
    set<pair<lli, int>> ff;
    timet[0] = antenne[0].s;
    ff.insert({timet[0], 0});
    int curr_tresh_iter = 0;

    while(!ff.empty()){
        pair<lli, int> curr = *ff.begin();
        ff.erase(ff.begin());

        lli t = curr.first;
        int node = curr.second;
        //cout<<"node "<<node<<", time "<<t<<" ("<<timet[node]<<") power: "<<curr_pow<<"\n";
        if(node == n - 1) return t;

        while(curr_tresh_iter < n - 1 && antenne[ordine[curr_tresh_iter]].l <= antenne[node].p && timet[ordine[curr_tresh_iter]] == INF){
            timet[ordine[curr_tresh_iter]] = antenne[ordine[curr_tresh_iter]].nextt(t);
            ff.insert({timet[ordine[curr_tresh_iter]], ordine[curr_tresh_iter]});
            //cout<<"can reach "<<ordine[curr_tresh_iter]<<" @ "<<timet[ordine[curr_tresh_iter]]<<" ("<<antenne[ordine[curr_tresh_iter]].l<<")\n";
            curr_tresh_iter++;
        }
    }
    return -1;
}

int main(){
    cin >> n >> d;
    for(int i = 0; i < n; i++)
        cin >> antenne[i].l >> antenne[i].p >> antenne[i].s >> antenne[i].t;

    for(int i = 0; i < n; i++)
        antenne[i].p+= d*i, antenne[i].l+= d*i;
    for(int i = 0; i < n - 1; i++)
        ordine[i] = i + 1;

    sort(ordine, ordine + n - 1, antennasort);
    /*for(int i = 0; i < n - 1; i++){
        cout<<ordine[i]<<": ", antenne[ordine[i]].print();
    }*/
    cout<<solve()<<"\n";
}
