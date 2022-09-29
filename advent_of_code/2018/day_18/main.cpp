#include <bits/stdc++.h>
#define MAXN 51
#define MAXT 1000000000
using namespace std;

char mappa[2][MAXN][MAXN];
int N = 0, M = 0;

int movR[] = {-1, -1, -1, 0, 0, 1, 1, 1}, movC[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void stampaMappa(int T){
    T%= 2;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++)
            cout<<mappa[T][i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

inline bool inRange(int i, int j){
    return (i >= 0 && j >= 0 && i < N && j < M);
}

int countSurr(int T, int i, int j, char what){
    T%= 2;
    int S = 0;
    for(int m = 0; m < 8; m++){
        if(inRange(i + movR[m], j + movC[m]) && mappa[T][i + movR[m]][j + movC[m]] == what)
            S++;
    }
    return S;
}

void itera(int T){
    int oldT = T - 1;
    T%= 2;
    oldT%= 2;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            mappa[T][i][j] = mappa[oldT][i][j];
            if(mappa[oldT][i][j] == '.'){
                if(countSurr(oldT, i, j, '|') >= 3)
                    mappa[T][i][j] = '|';
            }
            else if(mappa[oldT][i][j] == '|'){
                if(countSurr(oldT, i, j, '#') >= 3)
                    mappa[T][i][j] = '#';
            }
            else if(mappa[oldT][i][j] == '#'){
                if(countSurr(oldT, i, j, '#') < 1 || countSurr(oldT, i, j, '|') < 1)
                    mappa[T][i][j] = '.';
            }
        }
    }
}

int calcValue(int T){
    T%= 2;
    int lumbs = 0, trees = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(mappa[T][i][j] == '|')
                trees++;
            else if(mappa[T][i][j] == '#')
                lumbs++;
        }
    }
    return trees*lumbs;
}

int main(){
    fstream in, out;
    in.open("input18.txt", ios::in);
    out.open("output18.txt", ios::out);

    char inputTxt[MAXN];
    while(in.getline(inputTxt, MAXN)){
        M = strlen(inputTxt);
        for(int i = 0; i < M; i++)
            mappa[0][N][i] = inputTxt[i];
        N++;
    }
    //cout<<N<<" "<<M<<endl;
    //stampaMappa(0);
    cout<<0<<" -> "<<calcValue(0)<<endl;
    out<<calcValue(0);
    for(int t = 1; t < MAXT; t++){
        itera(t);
        //stampaMappa(t);
        cout<<t<<" -> "<<calcValue(t)<<endl;
        out<<t<<" -> "<<calcValue(t)<<"\n";
    }
    cout<<calcValue(MAXT - 1);
}
