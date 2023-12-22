#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
char a[MAXN];

int padre[MAXN];
int setsize[MAXN];
int pNum[MAXN];

int get_padre(int i){
    if(padre[i] == i) return i;
    return padre[i] = get_padre(padre[i]);
}

void join_sets(int i, int j){
    i = get_padre(i), j = get_padre(j);

    if(setsize[i] > setsize[j])
        padre[j] = i;
    else if(setsize[j] > setsize[i])
        padre[i] = j;
    else
        padre[i] = j, setsize[j]++;
}

void init(){
    cin >> n;
    cin >> a;

    for(int i = 0; i < n; i++)
        padre[i] = i;

    memset(setsize, 0, sizeof setsize);
}

int solve(){
    stack<int> zeros, ones;

    for(int i = 0; i < n; i++){
        if(a[i] == '0'){
            if(ones.size() > 0){
                int lst = ones.top();
                ones.pop();
                join_sets(i, lst);
            }
            zeros.push(i);
        }
        if(a[i] == '1'){
            if(zeros.size() > 0){
                int lst = zeros.top();
                zeros.pop();
                join_sets(i, lst);
            }
            ones.push(i);
        }
    }

    return zeros.size() + ones.size();
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
        set<int> padri;
        for(int i = 0; i < n; i++)
            padri.insert(get_padre(i));

        int k = 0;
        for(auto p:padri)
            pNum[p] = ++k;

        for(int i = 0; i < n; i++){
            cout<<pNum[get_padre(i)]<<" ";
        }
        cout<<"\n";
    }
}
