#include <bits/stdc++.h>
#define MAXN 155
#define MAXC 17
using namespace std;

enum {UP, RIGHT, DOWN, LEFT};

int N = 0, M = 0, C = 0;

int movR[] = {-1, 0, 1, 0}, movC[] = {0, 1, 0, -1};
int backSlash[] = {LEFT, DOWN, RIGHT, UP}, slash[] = {RIGHT, UP, LEFT, DOWN};
char mappa[MAXN][MAXN];
int mappaCarts[MAXN][MAXN];

int cartsRem;
bool collisione = false;
int rPrimaCollisione, cPrimaCollisione;

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

struct cartInfo{
    int id;
    int r;
    int c;
    int dire;
    int lastTurn; // prima a sinistra, poi a destra, infine in avanti
    bool alive;
    struct cartInfo *carts;

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

    void kill(){
        alive = false;
        mappaCarts[r][c] = -1;
        cartsRem--;
    }

    bool muovi(){
        mappaCarts[r][c] = -1;
        if(!alive)
            return false;

        r+= movR[dire];
        c+= movC[dire];
        if(mappaCarts[r][c] != -1){
            int cartPrecedente = mappaCarts[r][c];
            if(!collisione){
                collisione = true;
                rPrimaCollisione = r;
                cPrimaCollisione = c;
            }
            this->kill();
            carts[cartPrecedente].kill();
        }
        else{
            mappaCarts[r][c] = id;
            char ground = this->readPos();
            if(ground == '/')
                dire = slash[dire];
            else if(ground == '\\')
                dire = backSlash[dire];
            else if(ground == '+'){
                if(lastTurn%3 == 0)
                    dire = (dire + 3)%4;
                else if(lastTurn%3 == 2)
                    dire = (dire + 1)%4;
                lastTurn++;
            }
        }
        return true;
    }
} carts[MAXC];

void stampaMappa(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(mappaCarts[i][j] != -1)
                cout<<"c ";
            else
                cout<<mappa[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    fstream in;
    in.open("input13.txt", ios::in);

    char strMappa[MAXN];
    for(int i = 0; i < MAXN; i++)
        fill(mappaCarts[i], mappaCarts[i] + MAXN, -1);
    while(in.getline(strMappa, MAXN)){
        for(int i = 0; i < MAXN && strMappa[i] != '\0'; i++){
            if(strMappa[i] == 'v')
                strMappa[i] = 'V';
            if(isCart(strMappa[i])){
                carts[C] = {C, N, i, getDire(strMappa[i]), 0, 1, carts};
                mappaCarts[N][i] = C;
                mappa[N][i] = cartToTrack(strMappa[i]);
                C++;
            }
            else{
                mappa[N][i] = strMappa[i];
                mappaCarts[N][i] = -1;
            }
            M = max(M, i + 1);
        }
        N++;
    }

    //stampaMappa();

    cartsRem = C;
    queue<int> rim;

    while(cartsRem > 1){
        cout<<cartsRem<<"\r";
        //stampaMappa();
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(mappaCarts[i][j] != -1)
                    rim.push(mappaCarts[i][j]);
            }
        }
        while(!rim.empty()){
            int cart = rim.front();
            rim.pop();
            carts[cart].muovi();
        }
    }

    cout<<"La prima collisione e' avvenuta a "<<cPrimaCollisione<<","<<rPrimaCollisione<<endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(mappaCarts[i][j] != -1)
                cout<<"Cart in posizione "<<j<<","<<i<<endl;
        }
    }
}
