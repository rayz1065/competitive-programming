#include <bits/stdc++.h>
#define MAXP 1000000
#define MAXR 1000000

using namespace std;

int goesTo[110];
int plaPos[MAXP];
int P, R;

void init(){
    int snakeN;
    cin >> P >> snakeN >> R;
    for(int i = 1; i <= P; i++)
        plaPos[i] = 1;
    for(int i = 1; i <= 100; i++)
        goesTo[i] = i;
    for(int i = 0; i < snakeN; i++){
        int da, a;
        cin >> da >> a;
        goesTo[da] = a;
    }
}

int main(){
    FILE *out = stdout;

    int T;
    cin >> T;
    for(int i = 101; i < 110; i++)
        goesTo[i] = 100;

    for(int t = 1; t <= T; t++){
        init();
        bool gameOver = false;
        for(int r = 0; r < R; r++){
            int curr = r%P + 1, roll;
            cin >> roll;
            if(!gameOver){
                plaPos[curr] = goesTo[plaPos[curr] + roll];
                if(plaPos[curr] == 100)
                    gameOver = true;
            }
        }
        for(int i = 1; i <= P; i++)
            fprintf(out, "Position of player %d is %d.\n", i, plaPos[i]);
    }
}
