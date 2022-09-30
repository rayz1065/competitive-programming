#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string numero;
    cin>>numero;

    int N = numero.size();

    int riga[] = {3, 0, 0, 0, 1, 1, 1, 2, 2, 2};
    int colonna[] = {1, 0, 1, 2, 0, 1, 2, 0, 1, 2};
    int R = 3, C = 1;

    int S = 0;

    for(int i = 0; i < N; i++){
        int a = numero[i] - '0';
        S+= abs(R - riga[a]) + abs(C - colonna[a]) + 1;
        R = riga[a], C = colonna[a];
    }

    cout<<S;
}
