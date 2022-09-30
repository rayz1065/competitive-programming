#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

#define MAXST (MAXN*4)
#define S1(k) (k<<1)
#define S2(k) ((k<<1) + 1)

struct st_node{
    int v;
    int lazy;
} st[MAXST];

void lazy_propagation(int A, int B, int k){
    if(st[k].lazy){
        st[k].v+= st[k].lazy;
        if(S1(k) < MAXST)
            st[S1(k)].lazy+= st[k].lazy, st[S2(k)].lazy+= st[k].lazy;

        st[k].lazy = 0;
    }
}

int _update_range(int a, int b, int A, int B, int k, int am){
    lazy_propagation(A, B, k);
    if(b < A || a > B){
        return st[k].v;
    }
    if(a <= A && B <= b){
        st[k].lazy+= am;
        return st[k].v + st[k].lazy;
    }
    int mid = (A + B)/2;
    st[k].v = max(_update_range(a, b, A,       mid, S1(k), am),
                  _update_range(a, b, mid + 1,   B, S2(k), am));
    return st[k].v;

}

int _greater_range(int a, int b, int A, int B, int k){
    lazy_propagation(A, B, k);

    if(b < A || a > B) return -1;
    if(a <= A && B <= b)
        return st[k].v;
    int mid = (A + B)/2;
    return max(_greater_range(a, b, A,       mid, S1(k)),
               _greater_range(a, b, mid + 1,   B, S2(k)));
}

void update_range(int a, int b, int am){
    if(am)
        _update_range(a, b, 0, MAXN, 1, am);
}

int greater_range(int a, int b){
    return _greater_range(a, b, 0, MAXN, 1);
}

int N;

int comp_note[MAXN];
int notes[MAXN];

int long_seq[MAXN];
int long_compl[MAXN];

int add_note(int note){
    int m = long_seq[note];
    m = max(m, long_compl[note] + 1); // come complementaria
    m = max(m, greater_range(0, note - 1) + 1); // con una nota minore
    update_range(note, note, m - long_seq[note]);

    long_compl[comp_note[note]] = max(long_compl[comp_note[note]], m);
    return long_seq[note] = m;
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> notes[i];
    for(int i = 0; i < N; i++)
        cin >> comp_note[i + 1];

    int s = 0;
    for(int i = 0; i < N; i++){
        s = max(s, add_note(notes[i]));
    }

    cout<<s<<"\n";
}
