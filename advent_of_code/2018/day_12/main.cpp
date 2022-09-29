#include <bits/stdc++.h>
#define MAX_STATI 32
#define MAXN 100000
#define POS_ZERO 5
#define GEN 50000000001
using namespace std;

bitset<MAXN> flowey[2];
int Ncomp = 0;
bool comparatori[MAX_STATI][5];

void getIndexes(int r, int &posMin, int &posMax){
    posMin = 0, posMax = MAXN - 1;
    while(posMin < MAXN && !flowey[r%2][posMin])
        posMin++;
    while(posMax >= 0 && !flowey[r%2][posMax])
        posMax--;
}

void print(int r){
    int posMin, posMax;
    getIndexes(r, posMin, posMax);
    cout<<posMin<<" >> ";
    for(int i = posMin; i <= posMax; i++)
        cout<<((flowey[r%2][i])?'#':'.');
    cout<<" << "<<posMax<<"\n";
}

bool comp(int r, int c, int t){
    assert(c - 2 >= 0 && c + 2 < MAXN);
    for(int i = 0; i < 5; i++){
        if(flowey[r%2][i + c - 2] != comparatori[t][i])
            return false;
    }
    return true;
}

int main(){
    fstream in, out;
    in.open("input12.txt", ios::in);
    out.open("output12.txt", ios::out);

    char initialState[200];
    in.getline(initialState, 200);

    int i = 0;
    while(initialState[i] != '\0' && initialState[i] != '.' && initialState[i] != '#')
        i++;

    for(int p = 0; p < MAXN && initialState[i] != '\0'; i++)
        flowey[0][(p++) + POS_ZERO] = (initialState[i] == '#');

    char compString[100];

    while(in.getline(compString, 100)){
        if(compString[0] != '\0' && compString[9] == '#'){
            for(int i = 0; i < 5; i++)
                comparatori[Ncomp][i] = (compString[i] == '#');
            Ncomp++;
        }
    }
    for(int g = 1; g < GEN; g++){
        int posMin, posMax;
        getIndexes(g - 1, posMin, posMax);
        for(int c = posMin - 2; c <= posMax + 2; c++){
            for(int t = 0; t < Ncomp && !flowey[g%2][c]; t++){
                flowey[g%2][c] = comp(g - 1, c, t);
            }
        }
        int S = 0;

        getIndexes(g, posMin, posMax);
        for(int i = posMin; i <= posMax; i++){
            S+= flowey[g%2][i]*(i - POS_ZERO);
        }
        cout<<S<<" ";
        out<<S<<" ";
        //cout<<((g < 10)?" ":"")<<g<<": ";
        //print(g - 1);
    }
}
