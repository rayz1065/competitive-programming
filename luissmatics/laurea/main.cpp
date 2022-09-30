#include <bits/stdc++.h>
#define mezzi 4
using namespace std;

int posti[mezzi] = {2, 4, 5, 7};
int disp[mezzi];
int prezzo[mezzi];
int S = INT_MAX;

void solve(int m, int N, int P){
    if(m == mezzi - 1){
        int nec = N/posti[m] + (N % posti[m] > 0);
        if(nec > disp[m])
            return;
        int tot = P + prezzo[m]*nec;
        if(tot < S)
            S = tot;
        return;
    }
    for(int i = 0; i <= disp[m] && i * posti[m] <= N + (N % posti[m]); i++){
        solve(m + 1, N - i * posti[m], P + i * prezzo[m]);
    }
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    for(int i = 0; i < mezzi; i++)
        in>>disp[i]>>prezzo[i];

    solve(0, N, 0);
    out<<S;
}
