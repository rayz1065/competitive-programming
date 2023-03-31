#include <bits/stdc++.h>
#define MAXM 1005
#define MAXN 1005
using namespace std;

int numEventi, M;
pair<int, int> eventi[MAXN];
fstream in, out;

bool solved[MAXN][MAXM][2];
int memo[MAXN][MAXN][2];

int solve(int ev, int lastPos, bool wasLastPosR){
    if(solved[ev][lastPos][wasLastPosR])
        return memo[ev][lastPos][wasLastPosR];
    solved[ev][lastPos][wasLastPosR] = true;

    if(ev == numEventi)
        return 0;

    int posR, posC;
    if(ev == 0)
        posR = 1, posC = 1;
    else if(wasLastPosR)
        posR = lastPos, posC = eventi[ev - 1].second;
    else
        posC = lastPos, posR = eventi[ev - 1].first;

    int muoveR = solve(ev + 1, posC, false) + abs(posR - eventi[ev].first);
    int muoveC = solve(ev + 1, posR, true) + abs(posC - eventi[ev].second);

    //cout<<"Da "<<ev<<" "<<lastPos<<" "<<wasLastPosR<<" -> min("<<muoveR<<", "<<muoveC<<")\n";
    return memo[ev][lastPos][wasLastPosR] = min(muoveR, muoveC);
}

void stampa(int ev, int lastPos, bool wasLastPosR){
    if(ev == numEventi)
        return ;

    int posR, posC;
    if(ev == 0)
        posR = 1, posC = 1;
    else if(wasLastPosR)
        posR = lastPos, posC = eventi[ev - 1].second;
    else
        posC = lastPos, posR = eventi[ev - 1].first;

    int muoveR = solve(ev + 1, posC, false) + abs(posR - eventi[ev].first);
    int muoveC = solve(ev + 1, posR, true) + abs(posC - eventi[ev].second);

    if(muoveR < muoveC){
        out<<"R\n";
        stampa(ev + 1, posC, false);
    }
    else{
        out<<"C\n";
        stampa(ev + 1, posR, true);
    }
}

int main(){
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> numEventi >> M;
    for(int i = 0; i < numEventi; i++){
        int r, c;
        in >> r >> c;
        eventi[i] = {r, c};
    }

    solve(0, 1, 0);
    stampa(0, 1, 0);
}
