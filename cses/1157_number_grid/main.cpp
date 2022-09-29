#include <bits/stdc++.h>
#define MAXN 50
using namespace std;

int numeri[MAXN][MAXN];
int inserisci(int i, int j, int val){
    int k = i - 1;
    while(k >= 0){
        if(numeri[k][j] == val)
            return inserisci(i, j, val + 1);
        k--;
    }
    k = j - 1;
    while(k >= 0){
        if(numeri[i][k] == val)
            return inserisci(i, j, val + 1);
        k--;
    }
    numeri[i][j] = val;
    return 0;
}

int getSpaces(int N){
    int spacesMax = 2;
    if(N == 0)
        return spacesMax;
    return spacesMax - (int)log10(N);
}

int main(){
    int x, y;
    cin>>x>>y;
    cout<<((x - 1)^(y - 1));
    /*for(int i = 0; i < MAXN; i++){
        for(int j = 0; j < MAXN; j++)
            inserisci(i, j, 0);
    }
    for(int i = 0; i < MAXN; i++){
        for(int j = 0; j < MAXN; j++)
            cout<<numeri[i][j]<<string(getSpaces(numeri[i][j]), ' ');
        cout<<endl<<endl;
    }*/
    //#include<iostream>
    //int main(){int x,y;std::cin>>x>>y;x--,x^=y-1;std::cout<<x;}
}
