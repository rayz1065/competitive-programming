#include <bits/stdc++.h>
using namespace std;

int nodi, N, altMax;
set<int> attrazioni;
multiset<int> mancanti;
multiset<int> toBeErased;

void soluzione(){
    if(mancanti.empty()){
        for(auto altezza:attrazioni)
            cout<<altezza<<" ";
        exit(0);
    }

    bool maybe = true;
    int newAltezza = *mancanti.rbegin();
    if(!attrazioni.count(newAltezza)){
        toBeErased.clear();
        for(int alt:attrazioni)
            if(mancanti.count(abs(newAltezza - alt)) - toBeErased.count(abs(newAltezza - alt)) == 0)
                maybe = false;
            else
                toBeErased.insert(abs(newAltezza - alt));

        if(maybe){
            for(int alt:attrazioni)
                mancanti.erase(mancanti.find(abs(newAltezza - alt)));
            attrazioni.insert(newAltezza);
            soluzione();
            attrazioni.erase(newAltezza);
            for(int alt:attrazioni)
                mancanti.insert(abs(newAltezza - alt));
        }
    }
    newAltezza = altMax - *mancanti.rbegin();
    if(!attrazioni.count(newAltezza)){
        toBeErased.clear();
        maybe = true;
        for(int alt:attrazioni)
            if(mancanti.count(abs(newAltezza - alt)) - toBeErased.count(abs(newAltezza - alt)) == 0)
                maybe = false;
            else
                toBeErased.insert(abs(newAltezza - alt));

        if(maybe){
            for(int alt:attrazioni)
                mancanti.erase(mancanti.find(abs(newAltezza - alt)));
            attrazioni.insert(newAltezza);

            soluzione();

            attrazioni.erase(newAltezza);
            for(int alt:attrazioni)
                mancanti.insert(abs(newAltezza - alt));
        }
    }
}

int main(){
    fstream in;
    in.open("input.txt", ios::in);
    in>>nodi;
    N = (nodi*(nodi-1))/2;

    attrazioni.insert(0);
    for(int i=0; i<N; i++){
        int dist;
        in>>dist;
        mancanti.insert(dist);
    }
    altMax = *mancanti.rbegin();
    attrazioni.insert(altMax);
    mancanti.erase(mancanti.find(altMax));
    soluzione();
}
