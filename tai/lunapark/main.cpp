#include<bits/stdc++.h>
#define MAXN 1000005
#define MAXM 5000005

using namespace std;

struct strada{
    int da;
    int a;
    int peso;

    bool operator < (strada b){
        return peso > b.peso;
    }
};

int n, m, k;
strada strade[MAXM];
int padre[MAXN];
int set_rank[MAXN];

int get_padre(int a){
    if(a == padre[a]) return a;
    return padre[a] = get_padre(padre[a]);
}

bool merge_set(int a, int b){
    a = get_padre(a), b = get_padre(b);

    if(a == b) return false;
    if     (set_rank[a] < set_rank[b]) padre[a] = b;
    else if(set_rank[b] < set_rank[a]) padre[b] = a;
    else padre[a] = b, set_rank[b]++;
    return true;
}

int progetta(int n, int m, int k, vector<int> &a, vector<int> &b, vector<int> &w){
    ::n = n, ::m = m, ::k = k;

    for(int i = 0; i < m; i++)
        strade[i] = {a[i] - 1, b[i] - 1, w[i]};
    sort(strade, strade + m);

    for(int i = 0; i < n; i++)
        padre[i] = i;

    int isole = n, s = 0;
    for(int i = 0; i < m && isole > k; i++){
        if(merge_set(strade[i].da, strade[i].a)) isole--, s+= strade[i].peso;
    }
	return s;
}
