#include <bits/stdc++.h>
#define MAXN 1000005
#define gc() getchar_unlocked() // getchar
using namespace std;

int padre[MAXN];
int ranking[MAXN];

void readInt(int &N){
    char c;
    N = 0;
    c = gc();
    while(c < '0' || c > '9')
        c = gc();
    while(c >= '0' && c <= '9'){
        N = N*10 + c - '0';
        c = gc();
    }
}

int getPadre(int nodo){
    if(padre[nodo] != nodo)
        return padre[nodo] = getPadre(padre[nodo]);
    return nodo;
}

bool sameSet(int a, int b){
    return (getPadre(a) == getPadre(b));
}

int main(){
    int N, Q;
    cin >> N >> Q;

    for(int i = 0; i < N; i++)
        padre[i] = i, ranking[i] = 0;

    char op;
    int a, b;
    for(int i = 0; i < Q; i++){
        cin >> op;
        readInt(a);
        readInt(b);
        if(op == '?')
            cout<<((sameSet(a, b))?"yes":"no")<<"\n";
        else{
            int padreA = getPadre(a), padreB = getPadre(b);
            if(padreA != padreB){
                if(ranking[padreA] > ranking[padreB])
                    padre[padreB] = padreA;
                else if(ranking[padreA] < ranking[padreB])
                    padre[padreA] = padreB;
                else
                    padre[padreA] = padreB, ranking[padreB]++;
            }
        }
    }
}
