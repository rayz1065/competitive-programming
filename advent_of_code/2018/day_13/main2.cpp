#include <bits/stdc++.h>
#define MAXN 155
#define MAXC 18
using namespace std;

enum {UP, RIGHT, DOWN, LEFT};
enum {FREE, OCCUPIED, COLLISION};
int N = 0, M = 0, C = 0;
int movR[] = {-1, 0, 1, 0}, movC[] = {0, 1, 0, -1};
char mappa[MAXN][MAXN];
int mappaCarts[MAXN][MAXN];

struct cartInfo{
    int r;
    int c;
    int dire;
    int lastTurn; // prima a sinistra, poi a destra, infine in avanti
    bool alive;

    void stampa(){
        cout<<"Posizione: "<<r<<","<<c<<"\nDirezione: "<<dire<<"\nUltima curva: "<<lastTurn<<"\nVivo: "<<alive<<"\n\n";
    }

    bool operator <(cartInfo B){
        if(!alive && B.alive)
            return false;
        if(!B.alive && alive)
            return true;
        if(r < B.r)
            return true;
        return c < B.c;
    }

    char readPos(){
        return mappa[r][c];
    }
} carts[MAXC];

bool isCart(char c){
    return (c == '^' || c == 'V' || c == '<' || c == '>');
}

int getDire(char c){
    if(c == '^')
        return UP;
    if(c == '>')
        return RIGHT;
    if(c == 'V')
        return DOWN;
    if(c == '<')
        return LEFT;
    return -1;
}

char cartToTrack(char c){
    return ((c == '^' || c == 'V')?'|':'-');
}

int main(){
    fstream in;
    in.open("input13.txt", ios::in);

    char strMappa[MAXN];
    while(in.getline(strMappa, MAXN)){
        for(int i = 0; i < MAXN && strMappa[i] != '\0'; i++){
            if(strMappa[i] == 'v')
                strMappa[i] = 'V';
            if(isCart(strMappa[i])){
                carts[C] = {N, i, getDire(strMappa[i]), 0, 1};
                mappaCarts[N][i] = OCCUPIED;
                mappa[N][i] = cartToTrack(strMappa[i]);
                C++;
            }
            else{
                mappa[N][i] = strMappa[i];
                mappaCarts[N][i] = FREE;
            }
            M = max(M, i);
        }
        N++;
    }
    M++;

    bool collisione = false;
    int rPrimaCollisione, cPrimaCollisione;

    /*for(int i = 0; i < C; i++){
        cout<<"cart "<<i<<endl;
        carts[i].stampa();
        cout<<endl;
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(mappaCarts[i][j] == OCCUPIED)
                cout<<"c ";
            else if(mappaCarts[i][j] == COLLISION)
                cout<<"X ";
            else
                cout<<mappa[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;*/
    int cartsRem = C;
    while(cartsRem > 1){
        sort(carts, carts + C);
        for(int i = 0; i < C; i++){
            if(carts[i].alive && mappaCarts[carts[i].r][carts[i].c] == FREE){
                carts[i].alive = false;
                cartsRem--;
            }
            if(carts[i].alive){
                if(cartsRem == 1)
                    carts[i].stampa();
                mappaCarts[carts[i].r][carts[i].c] = FREE;
                carts[i].r+= movR[carts[i].dire];
                carts[i].c+= movC[carts[i].dire];
                if(mappaCarts[carts[i].r][carts[i].c] != FREE){
                    if(!collisione){
                        collisione = true;
                        rPrimaCollisione = carts[i].r;
                        cPrimaCollisione = carts[i].c;
                    }
                    carts[i].alive = false;
                    cartsRem--;
                    mappaCarts[carts[i].r][carts[i].c] = FREE;
                }
                else{
                    mappaCarts[carts[i].r][carts[i].c] = OCCUPIED;
                    char ground = carts[i].readPos();
                    if(ground == '/'){
                        if(carts[i].dire == UP)
                            carts[i].dire = RIGHT;
                        else if(carts[i].dire == LEFT)
                            carts[i].dire = DOWN;
                        else if(carts[i].dire == DOWN)
                            carts[i].dire = LEFT;
                        else if(carts[i].dire == RIGHT)
                            carts[i].dire = UP;
                    }
                    else if(ground == '\\'){
                        if(carts[i].dire == UP)
                            carts[i].dire = LEFT;
                        else if(carts[i].dire == LEFT)
                            carts[i].dire = UP;
                        if(carts[i].dire == DOWN)
                            carts[i].dire = RIGHT;
                        else if(carts[i].dire == RIGHT)
                            carts[i].dire = DOWN;
                    }
                    else if(ground == '+'){
                        if(carts[i].lastTurn%3 == 0){
                            carts[i].dire = (carts[i].dire + 3)%4;
                        }
                        else if(carts[i].lastTurn%3 == 2){
                            carts[i].dire = (carts[i].dire + 1)%4;
                        }
                        carts[i].lastTurn++;
                    }
                }
            }
            /*this_thread::sleep_for(chrono::milliseconds(250));
            system("cls");
            for(int i = 0; i < N; i++){
                for(int j = 0; j < M; j++){
                    if(mappaCarts[i][j] == OCCUPIED)
                        cout<<"c ";
                    else if(mappaCarts[i][j] == COLLISION)
                        cout<<"X ";
                    else
                        cout<<mappa[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
            /*for(int i = 0; i < C; i++){
                cout<<"cart "<<i<<endl;
                carts[i].stampa();
                cout<<endl;
            }*/
        }
    }
    sort(carts, carts + C);
    carts[0].stampa();
    cout<<"La prima collisione e' avvenuta a "<<cPrimaCollisione<<","<<rPrimaCollisione<<endl;
}
