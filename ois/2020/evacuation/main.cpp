#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n;
int p[MAXN];
int arrog[MAXN];
int ordine[MAXN];
bool passed[MAXN];

struct listnode{
    int i;
    listnode *nxt;

    listnode(int _i, listnode *_nxt){
        i = _i, nxt = _nxt;
    }

    listnode(int _i){
        i = _i, nxt = NULL;
    }

    listnode(){
        i = -1, nxt = NULL;
    }

    void append(listnode *b){
        nxt = b;
    }

    void print(){
        cout<<i<<" ";
        //cout<<i<<": "<<arrog[i]<<", passed: "<<passed[i]<<"\n";
    }
};

struct mylist{
    listnode *beg;
    listnode *fin;

    mylist(int i){
        listnode *temp = new listnode(i);
        beg = fin = temp;
    }

    mylist(listnode *node){
        beg = node, fin = node;
    }

    mylist(){
        beg = fin = NULL;
    }

    void append(mylist b){
        fin -> append(b.beg);
        fin = b.fin;
    }

    int getv(){
        return beg -> i;
    }

    bool isempty(){
        return beg == NULL;
    }

    bool pop(){
        if(isempty()) return false;
        listnode *temp = beg;
        beg = beg -> nxt;
        free(temp);
        return true;
    }

    void print(){
        listnode *temp = beg;
        while(temp != NULL){
            temp -> print();
            temp = temp -> nxt;
        }
        cout<<"\n";
    }
};

mylist currqueues[MAXN];

bool arrorder(int i, int j){
    return arrog[i] > arrog[j];
}

int risali(int i){
    if(!passed[i]) return i;
    return p[i] = risali(p[i]);
}

void solve(){
    for(int j = 0; j < n - 1; j++){
        int i = ordine[j];
        passed[i] = true;
        int gt = risali(i);
        currqueues[gt].append(currqueues[i]);
    }
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> p[i];

    for(int i = 0; i < n; i++){
        cin >> arrog[i];
        ordine[i] = i;
        passed[i] = false;
    }
    arrog[0] = -1;
    sort(ordine, ordine + n, arrorder);

    for(int i = 0; i < n; i++)
        currqueues[i] = mylist(i);

    solve();
    currqueues[0].print();
}
