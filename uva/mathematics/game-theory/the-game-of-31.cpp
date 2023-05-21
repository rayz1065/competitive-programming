#include <bits/stdc++.h>

using namespace std;

bool willWin(int cards[], int j, int S){
    if(S>=31)
        return false;
    if(j!=-1)
        cards[j]--;
    for(int i=0; i<6&&S+i+1<=31; i++){
        if(cards[i]>0){
            if(!willWin(cards, i, S+i+1)){
                cards[j]++;
                return true;
            }
        }
    }
    cards[j]++;
    return false;
}

int main(){
    long long game;
    while(cin>>game){
        int N=log10(game)+1;
        int S=0;
        int cards[7];
        for(int i=0; i<6; i++)
            cards[i]=4;
        for(int i=game; i>0; i/=10){
            cards[i%10-1]--;
            S+=i%10;
        }
        cout<<game<<" "<<(abs(N%2-willWin(cards, 6, S))?'A':'B')<<endl;
    }
}
