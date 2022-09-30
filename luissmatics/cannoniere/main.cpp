#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    int giocatori[100];
    for(int i=0; i<100; i++)
        giocatori[i]=0;
    int best=0;
    for(int i=0; i<N; i++){
        int player, goal;
        in>>player>>goal;
        giocatori[player]+=goal;
        if(giocatori[player]>giocatori[best])
            best=player;
    }
    out<<best<<" "<<giocatori[best];
}
