#include <bits/stdc++.h>
#define DEFEATTEXT "#####"
#define DEBUGMODE 0
#define DIM 4
using namespace std;

char griglia[DIM][DIM];

bool winCondition(int riga, int colonna){
    char player = griglia[riga][colonna];
    int diFila = 0;
    for(int i = 0; i < DIM && griglia[i][colonna] == player; i++)
        diFila++;
    if(diFila == 4)
        return true;
    diFila = 0;
    for(int i = 0; i < DIM && griglia[riga][i] == player; i++)
        diFila++;
    if(diFila == 4)
        return true;
    diFila = 0;
    for(int i = 0; i < DIM && griglia[i][i] == player; i++)
        diFila++;
    if(diFila == 4)
        return true;
    diFila = 0;
    for(int i = 0; i < DIM && griglia[i][DIM - i - 1] == player; i++)
        diFila++;
    if(diFila == 4)
        return true;
    return false;
}

bool willWin(char player){
    if(DEBUGMODE){
        cout<<player<<endl;
        for(int i = 0; i < DIM; i++){
            for(int j = 0; j < DIM; j++)
                cout<<griglia[i][j]<<" ";
            cout<<endl;
        }
        cout<<endl;
    }
    char nextPlayer = ((player == 'x')?'o':'x');

    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            if(griglia[i][j] == '.'){
                griglia[i][j] = player;
                if(winCondition(i, j)){
                    griglia[i][j] = '.';
                    return true;
                }

                griglia[i][j] = '.';
            }
        }
    }

    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            if(griglia[i][j] == '.'){
                griglia[i][j] = player;
                if(!willWin(nextPlayer)){
                    griglia[i][j] = '.';
                    return true;
                }

                griglia[i][j] = '.';
            }
        }
    }
    return false;
}

void testCase(){
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            if(griglia[i][j] == '.'){
                griglia[i][j] = 'x';
                if(winCondition(i, j) || !willWin('o')){
                    // soluzione trovata
                    cout<<"("<<i<<","<<j<<")\n";
                    if(DEBUGMODE)
                        system("PAUSE");
                    return;
                }
                if(DEBUGMODE)
                    system("PAUSE");
                griglia[i][j] = '.';
            }
        }
    }
    cout<<DEFEATTEXT<<"\n";
    if(DEBUGMODE)
        system("PAUSE");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    char next;
    cin>>next;
    while(next == '?'){ // ci sono altri casi
        for(int i = 0; i < DIM; i++)
            for(int j = 0; j < DIM; j++)
                cin>>griglia[i][j];
        testCase();
        cin>>next;
    }
}
