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

    for(int i = 0; i < MAXL; i++){
        if(i%100 == 0)
            cout<<"\r"<<i/10<<"%";
        for(int j = 0; j < MAXL; j++){
            vector<pair<int, int> > distanze;
            for(int c = 0; c < N; c++){
                int d = abs(X[c] - i) + abs(Y[c] - j);
                distanze.push_back({d, c});
            }
            sort(distanze.begin(), distanze.end());
            if(distanze[0].first == distanze[1].first)
                distances[i][j] = -1;
            else{
                distances[i][j] = distanze[0].second;
                aree[distances[i][j]]++;
            }
        }
    }
    cout<<"\r";

    for(int i = 0; i < MAXL; i++){
        if(distances[i][0] != -1)
            aree[distances[i][0]] = INT_MAX;
    }
    for(int i = 0; i < MAXL; i++){
        if(distances[i][MAXL - 1] != -1)
            aree[distances[i][MAXL - 1]] = INT_MAX;
    }
    for(int j = 0; j < MAXL; j++){
        if(distances[0][j] != -1)
            aree[distances[0][j]] = INT_MAX;
    }
    for(int j = 0; j < MAXL; j++){
        if(distances[MAXL - 1][j] != -1)
            aree[distances[MAXL - 1][j]] = INT_MAX;
    }
    sort(aree, aree + N);
    for(int i = 0; i < N; i++)
        cout<<aree[i]<<" ";
}
