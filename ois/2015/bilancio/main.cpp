#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int N, K;
int numero[MAXN];
int nextMinTable[MAXN][10];

int getNextMin(int a, int b, int num){
    if(num < 0)
        return a;
    int nextMin = nextMinTable[a][num];
    if(nextMin != -1 && nextMin <= b)
        return getNextMin(nextMin, b, num - 1);
    return a;
}

int trovaMin(int a, int b){
    return getNextMin(a, b, 9);
    int bestPos = a;
    for(int i = a; i < b; i++){
        if(numero[i] < numero[bestPos])
            bestPos = i;
    }
    return bestPos;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N >> K;

    for(int i = 0; i < N; i++)
        in>>numero[i];

    for(int i = 0; i < 10; i++)
        nextMinTable[N][i] = -1;

    for(int i = N - 1; i >= 0; i--){
        for(int j = 0; j < numero[i]; j++)
            nextMinTable[i][j] = nextMinTable[i + 1][j];
        for(int j = numero[i]; j < 10; j++)
            nextMinTable[i][j] = i;
    }
    /*for(int i = 0; i < N; i++)
        cout<<numero[i]<<"\t";
    cout<<endl;
    for(int j = 0; j < 10; j++){
        for(int i = 0; i < N; i++)
            cout<<nextMinTable[i][j]<<"\t";
        cout<<endl;
    }
    cout<<endl;*/

    int i = 0;
    while(K >= 0 && i < N && i + K < N){
        int bestPos = trovaMin(i, i + K);
        out<<numero[bestPos]<<" ";
        K-= bestPos - i;
        i = bestPos + 1;
    }
    out<<endl;
}
