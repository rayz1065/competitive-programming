#include <bits/stdc++.h>
#define MAXN 55
#define MAXL 1000
using namespace std;

int X[MAXN], Y[MAXN];
int distances[MAXL][MAXL];

int main(){
    fstream in, out;
    in.open("input6.txt", ios::in);

    char coordInfo[100];
    int N = 0, xMax = 0, yMax = 0;
    while(in.getline(coordInfo, 100)){
        int i = 0;
        while(coordInfo[i] >= '0' && coordInfo[i] <= '9')
            X[N] = X[N]*10 + coordInfo[i++] - '0';
        i+= 2;
        while(coordInfo[i] >= '0' && coordInfo[i] <= '9')
            Y[N] = Y[N]*10 + coordInfo[i++] - '0';
        X[N]+= 500;
        Y[N]+= 500;
        N++;
    }

    unsigned long long int aree[MAXN] = {};
    int regionePiacevole = 0;

    for(int i = 0; i < MAXL; i++){
        if(i%100 == 0)
            cout<<"\r"<<i/10<<"%";
        for(int j = 0; j < MAXL; j++){
            int dTot = 0;
            for(int c = 0; c < N; c++){
                int d = abs(X[c] - i) + abs(Y[c] - j);
                dTot+= d;
            }
            if(dTot < 10000)
                regionePiacevole++;
        }
    }
    cout<<"\r"<<regionePiacevole<<endl;

}
