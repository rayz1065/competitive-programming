#include <bits/stdc++.h>
#define DECKSIZE 52

using namespace std;

int carteA[3], carteB[3];
bool used[DECKSIZE + 1], usedA[3], usedB[3];

void stampaSit(){
    cout<<"Giocatore A: ";
    for(int i = 0; i < 3; i++)
        if(!usedA[i])
            cout<<carteA[i]<<" ";
    cout<<"\nGiocatore B: ";
    for(int i = 0; i < 3; i++)
        if(!usedB[i])
            cout<<carteB[i]<<" ";
    cout<<"\n";
}

int getWins(int t){
    if(t == 3)
        return 0;
    int S = 10, bestI = -1, bestJ = -1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; !usedA[i] && j < 3; j++){
            if(!usedB[j]){
                usedA[i] = usedB[j] = true;
                int f = getWins(t + 1) + (carteA[i] < carteB[j]);
                if(f < S)
                    S = f, bestI = i, bestJ = j;
                usedA[i] = usedB[j] = false;
            }
        }
    }
    return S;
}

bool willWin(){
    return (getWins(0) >= 2);
}

void iniz(){
    fill(used, used + DECKSIZE + 1, false);
    for(int i = 0; i < 3; i++){
        cin >> carteA[i];
        used[carteA[i]] = true;
    }
    for(int i = 0; i < 2; i++){
        cin >> carteB[i];
        used[carteB[i]] = true;
    }
    for(int i = 0; i < 3; i++)
        usedA[i] = usedB[i] = false;
}

int findMinNum(){
    for(int i = 1; i <= DECKSIZE; i++){
        if(!used[i]){
            carteB[2] = i;
            if(willWin())
                return i;
        }
    }
    return -1;
}

int main(){
    while(true){
        iniz();
        if(carteA[0] == 0)
            return 0;
        cout<<findMinNum()<<"\n";
    }
}
