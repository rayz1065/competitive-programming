#include <bits/stdc++.h>
#define MAXN 100001
using namespace std;

struct info{
    int somma;
    bool lazy;
} ST[MAXN*4];

int query(int L, int R, int a, int b, int k){
    if(b<L||a>R) return 0;
    if(ST[k].lazy){
        ST[k].somma=(b-a+1)-ST[k].somma;
        if(a!=b){
            ST[k<<1].lazy=1-ST[k<<1].lazy;
            ST[(k<<1)+1].lazy=1-ST[(k<<1)+1].lazy;
        }
        ST[k].lazy=false;
    }
    if(a>=L&&b<=R) return ST[k].somma;

    int media=(a+b)/2;
    return query(L, R, a, media, k<<1) + query(L, R, media+1, b, (k<<1)+1);
}

void update(int L, int R, int a, int b, int k){
    if(ST[k].lazy){
        ST[k].somma=(b-a+1)-ST[k].somma;
        if(a!=b){
            ST[k<<1].lazy=1-ST[k<<1].lazy;
            ST[(k<<1)+1].lazy=1-ST[(k<<1)+1].lazy;
        }
        ST[k].lazy=false;
    }

    if(b<L||a>R) return;

    if(a>=L&&b<=R){
        ST[k].somma=(b-a+1)-ST[k].somma;
        if(a!=b){
            ST[k<<1].lazy=1-ST[k<<1].lazy;
            ST[(k<<1)+1].lazy=1-ST[(k<<1)+1].lazy;
        }
        return;
    }

    int media = (a+b)/2;
    update(L, R, a, media, k<<1);
    update(L, R, media+1, b, (k<<1)+1);
    ST[k].somma = ST[k<<1].somma + ST[(k<<1)+1].somma;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N, Q;
    in>>N>>Q;
    for(int i=0; i<Q; i++){
        bool type;
        int a, b;
        in>>type>>a>>b;
        if(type)
            out<<query(a, b, 0, N-1, 1)<<endl;
        else
            update(a, b, 0, N-1, 1);
    }
}
