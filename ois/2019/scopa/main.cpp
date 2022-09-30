#include <bits/stdc++.h>

using namespace std;

struct carta{
    char tipo;
    int num;

    void stampa(){
        cout<<num<<" di "<<tipo<<endl;
    }

    void stampaS(){
        cout<<num<<tipo<<" ";
    }
};

carta tavolo[4], mano[3];
vector<carta> bestMove;
int bestScore = 0;

int getVal(carta A){
    int S = A.num;
    if(A.num == 7){
        S+= 100;
        if(A.tipo == 'G')
            S+= 10000;
    }
    return S;
}

void scegliCarte(int A, bool taken[], vector<carta> prese){
    if(A == 0){
        int S = 0;
        for(auto i:prese)
            S+= getVal(i);
        if(prese.size() == 5)
            S+= 5000;
        if(S > bestScore)
            bestMove = prese, bestScore = S;
        return ;
    }
    for(int i = 0; i < 4; i++){
        if(!taken[i] && A - tavolo[i].num >= 0){
            taken[i] = true;
            prese.push_back(tavolo[i]);
            scegliCarte(A - tavolo[i].num, taken, prese);
            taken[i] = false;
            prese.pop_back();
        }
    }
}

void calcolaPunti(carta A){
    bool taken[4] = {};

    scegliCarte(A.num, taken, {A});
}

int main(){
    for(int i = 0; i < 3; i++)
        cin>>mano[i].num>>mano[i].tipo;
    for(int i = 0; i < 4; i++)
        cin>>tavolo[i].num>>tavolo[i].tipo;

    for(int i = 0; i < 3; i++)
        calcolaPunti(mano[i]);
    for(auto i:bestMove)
        i.stampaS();
}
