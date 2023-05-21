#include <bits/stdc++.h>
#define MAXN 100005
#define SIZE_ST ((MAXN<<2) + 5)
#define MAXV 100005

#define LFT(x) (x<<1)
#define RGT(x) ((x<<1) + 1)
using namespace std;

int n, k;
int numeri[MAXN];
int numeri_freq_idx[MAXN];

int st[SIZE_ST];

int start_idx[MAXV*2];
int end_idx[MAXV*2];

int n_freq;
int freq[MAXN];

int _max_range(int A, int B, int a, int b, int k){
    if(b < A || a > B) return INT_MIN;
    if(a <= A && B <= b) return st[k];

    int mid = (A + B)/2;
    return max(_max_range(A, mid, a, b, LFT(k)), _max_range(mid + 1, B, a, b, RGT(k)));
}

int max_range(int a, int b){
    if(a > b) return 0;
    return _max_range(0, MAXN, a, b, 1);
}

int _st_update(int A, int B, int a, int b, int k, int v){
    if(b < A || a > B) return st[k];
    if(a <= A && B <= b){
        //cout<<"ora "<<a<<","<<b<<" ("<<k<<") vale "<<v<<"\n";
        return st[k] = v;
    }

    int mid = (A + B)/2;
    return st[k] = max(_st_update(A, mid, a, b, LFT(k), v), _st_update(mid + 1, B, a, b, RGT(k), v));
}

void st_update(int a, int v){
    //cout<<"update "<<a<<" set to "<<v<<"\n";
    _st_update(0, MAXN, a, a, 1, v);
}

void set_start_idx(int i, int v){
    start_idx[i + MAXV] = v;
}

void set_end_idx(int i, int v){
    end_idx[i + MAXV] = v;
}

int get_start_idx(int i){
    return start_idx[i + MAXV];
}

int get_end_idx(int i){
    return end_idx[i + MAXV];
}

bool init(){
    cin >> n;
    if(n == 0) return false;

    cin >> k;

    for(int i = 0; i < n; i++)
        cin >> numeri[i];

    int curr_freq = 1;
    n_freq = 0;
    set_start_idx(numeri[0], 0);
    numeri_freq_idx[0] = 0;

    for(int i = 1; i < n; i++){
        if(numeri[i] == numeri[i - 1])
            curr_freq++;
        else{
            set_end_idx(numeri[i - 1], i - 1);
            set_start_idx(numeri[i], i);

            freq[n_freq++] = curr_freq;
            curr_freq = 1;
        }
        numeri_freq_idx[i] = n_freq;
    }

    set_end_idx(numeri[n - 1], n - 1);
    freq[n_freq++] = curr_freq;

    for(int i = 0; i < n_freq; i++)
        st_update(i, freq[i]);

    return true;
}

void solve(){
    static FILE *out = stdout;//fopen("output.txt", "w");
    for(int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        int l_dim = min(b, get_end_idx(numeri[a])) - a + 1, r_dim = b - max(a, get_start_idx(numeri[b])) + 1;
        int edge_dim = max(l_dim, r_dim);
        int l_freq_idx = numeri_freq_idx[a], r_freq_idx = numeri_freq_idx[b];
        int range_dim = max_range(l_freq_idx + 1, r_freq_idx - 1);

        // cout<<"start: "<<a<<", "<<numeri[a]<<",\tfinisce a "<<get_end_idx(numeri[a])<<"\tdim = "<<l_dim<<"\n";
        // cout<<"fine : "<<b<<", "<<numeri[b]<<",\t inizia a "<<get_start_idx(numeri[b])<<"\tdim = "<<r_dim<<"\n";
        // cout<<"freq_idx left: "<<l_freq_idx<<"\nfreq_idx_right: "<<r_freq_idx<<"\n\n";
        // cout<<"edge: "<<edge_dim<<", range: "<<l_freq_idx + 1<<" -> "<<r_freq_idx - 1<<": "<<range_dim<<"\n";

        fprintf(out, "%d\n", max(edge_dim, range_dim));
    }
}

int main(){
    while(init()){
        solve();
    }
}
