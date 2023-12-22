#include <bits/stdc++.h>
#define MAXN 1000005
#ifdef _WIN32
    #define gc() getchar()
#else
    #define gc() getchar_unlocked()
#endif
using namespace std;

int N, M;
int padre[MAXN];
set<pair<int, pair<int, int> > > archi;
set<pair<int, int> > scelti;

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
    while(cin >> N >> M){
        if(N == 0 && M == 0)
            return 0;
        archi.clear();
        scelti.clear();
        for(int i = 0; i < N; i++)
            padre[i] = i;

        for(int i = 0; i < M; i++){
            int a, b, w;
            cin >> a >> b >> w;
            archi.insert({w, {a, b}});
        }

        int isole = N, cost = 0;
        while(isole > 1 && !archi.empty()){
            int a = archi.begin()->second.first, b = archi.begin()->second.second;
            if(getPadre(a) != getPadre(b)){
                cost+= archi.begin()->first;
                padre[getPadre(a)] = getPadre(b);
                isole--;
                scelti.insert({min(a, b), max(a, b)});
            }
            archi.erase(archi.begin());
        }
        if(isole > 1){
            cout<<"Impossible\n";
        }
        else{
            cout<<cost<<"\n";
            for(auto i:scelti){
                cout<<i.first<<" "<<i.second<<endl;
            }
        }
    }
}
