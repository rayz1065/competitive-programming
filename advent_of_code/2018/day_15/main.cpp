#include <bits/stdc++.h>
#define MAX_HITPOINTS 200
#define AD_GHOULS 3
#define AD_ELFS 19
#define MAXN 50
#define MAXE 50
#define DEBUGMODE false
using namespace std;

char mappa[MAXN][MAXN];
int mappaEntities[MAXN][MAXN];
int N = 0, M = 0, E = 0;

int movR[] = {-1, 0, 0, 1}, movC[] = {0, -1, 1, 0};
int ghouls = 0, elfs = 0;
int dist[MAXN][MAXN];

inline bool inRange(int r, int c){
    return (r >= 0 && c >= 0 && r < N && c < M);
}

struct entityInfo{
    int id;
    char tipo;
    int hp;
    int ad;
    int r;
    int c;
    bool vivo;
    struct entityInfo *entities;

    void stampa(){
        cout<<"Entita' "<<id<<":\nTipo: "<<((tipo == 'E')?"Elfo":((tipo == 'G')?"Ghoul":"Boh"))<<"\nHp: "<<hp<<", Ad: "<<ad<<"\nPosizione: "<<r<<","<<c<<"\nVivo? "<<((vivo)?"Si'":"No")<<endl<<endl;
    }

    void takeDamage(int danno){
        hp-= danno;
        if(hp <= 0){
            vivo = false;
            mappaEntities[r][c] = -1;
            if(tipo == 'G')
                ghouls--;
            else
                elfs--;
            if(DEBUGMODE)
                cout<<id<<" muore\n";
        }
    }

    bool attack(){
        if(!vivo)
            return false;
        int leastHp = MAX_HITPOINTS + 1, bestEntity;
        for(int i = 0; i < 4; i++){
            if(inRange(r + movR[i], c + movC[i])){
                int newR = r + movR[i], newC = c + movC[i], targetEntity = mappaEntities[newR][newC];
                if(targetEntity != -1 && entities[targetEntity].tipo != tipo){
                    if(entities[targetEntity].hp < leastHp){
                        leastHp = entities[targetEntity].hp;
                        bestEntity = entities[targetEntity].id;
                    }
                }
            }
        }
        if(leastHp == MAX_HITPOINTS + 1)
            return false;
        if(DEBUGMODE)
            cout<<id<<" attacca "<<bestEntity<<endl;
        entities[bestEntity].takeDamage(ad);
        return true;
    }

    bool muovi(){
        if(!vivo)
            return false;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++)
                dist[i][j] = INT_MAX;
        }
        queue<pair<int, int> > FF;
        FF.push({r, c});
        dist[r][c] = 0;
        int currR, currC;
        int bestDist = INT_MAX, bestR, bestC;
        while(!FF.empty()){
            currR = FF.front().first, currC = FF.front().second;
            FF.pop();
            for(int i = 0; i < 4; i++){
                if(inRange(currR + movR[i], currR + movC[i])){
                    int newR = currR + movR[i], newC = currC + movC[i], targetEntity = mappaEntities[newR][newC];
                    if(targetEntity != -1){
                        if(entities[targetEntity].tipo != tipo){
                            if(dist[currR][currC] < bestDist)
                                bestDist = dist[currR][currC], bestR = currR, bestC = currC;
                            else if(dist[currR][currC] == bestDist && ((currR < bestR) || (currR == bestR && currC < bestC))){
                                bestDist = dist[currR][currC], bestR = currR, bestC = currC;
                            }
                        }
                    }
                    else if(mappa[newR][newC] == '.' && dist[currR][currC] + 1 < dist[newR][newC]){
                        FF.push({newR, newC});
                        dist[newR][newC] = dist[currR][currC] + 1;
                    }
                }
            }
        }
        if(bestDist == INT_MAX){
            if(DEBUGMODE)
                cout<<id<<" non sa dove andare\n";
            /*for(int i = 0; i < N; i++){
                for(int j = 0; j < M; j++)
                    cout<<dist[i][j]<<" ";
                cout<<endl;
            }*/
            return false;
        }
        if(DEBUGMODE)
            cout<<id<<" vuole andare a "<<bestR<<","<<bestC<<endl;

        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++)
                dist[i][j] = INT_MAX;
        }
        FF.push({bestR, bestC});
        dist[bestR][bestC] = 0;
        while(!FF.empty()){
            currR = FF.front().first, currC = FF.front().second;
            FF.pop();
            for(int i = 0; i < 4; i++){
                if(inRange(currR + movR[i], currR + movC[i])){
                    int newR = currR + movR[i], newC = currC + movC[i], targetEntity = mappaEntities[newR][newC];
                    if(targetEntity == -1 && mappa[newR][newC] == '.' && dist[currR][currC] + 1 < dist[newR][newC]){
                        FF.push({newR, newC});
                        dist[newR][newC] = dist[currR][currC] + 1;
                    }
                }
            }
        }
        currR = r, currC = c;
        bestDist = INT_MAX;
        for(int i = 0; i < 4; i++){
            if(inRange(currR + movR[i], currR + movC[i])){
                int newR = currR + movR[i], newC = currC + movC[i], targetEntity = mappaEntities[newR][newC];
                if(targetEntity == -1 && mappa[newR][newC] == '.'){
                    if(dist[newR][newC] < bestDist)
                        bestDist = dist[newR][newC], bestR = newR, bestC = newC;
                }
            }
        }
        if(bestDist == INT_MAX){
            cout<<"errore con il movimento di "<<id<<endl;
            exit(1);
        }
        if(DEBUGMODE)
            cout<<id<<" si muove a "<<bestR<<" "<<bestC<<endl;
        mappaEntities[r][c] = -1;
        mappaEntities[bestR][bestC] = id;
        r = bestR, c = bestC;
        return true;
    }
} entities[MAXE];

void printMap(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(mappaEntities[i][j] == -1)
                cout<<mappa[i][j]<<" ";
            else
                cout<<entities[mappaEntities[i][j]].tipo<<" ";
        }
        cout<<"  ";
        int eRow = 0;
        for(int j = 0; j < M; j++){
            if(mappaEntities[i][j] != -1){
                if(eRow++ > 0)
                    cout<<", ";
                cout<<entities[mappaEntities[i][j]].tipo<<" ("<<entities[mappaEntities[i][j]].id<<"->"<<entities[mappaEntities[i][j]].hp<<")";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    fstream in, out;
    in.open("input15.txt", ios::in);

    char mappaTxt[MAXN];
    while(in.getline(mappaTxt, MAXN)){
        for(int j = 0; j < MAXN && mappaTxt[j] != '\0'; j++){
            if(mappaTxt[j] == 'G' || mappaTxt[j] == 'E'){
                if(mappaTxt[j] == 'G'){
                    ghouls++;
                    entities[E] = {E, mappaTxt[j], MAX_HITPOINTS, AD_GHOULS, N, j, 1, entities};
                }
                else{
                    elfs++;
                    entities[E] = {E, mappaTxt[j], MAX_HITPOINTS, AD_ELFS, N, j, 1, entities};
                }
                mappaEntities[N][j] = E;
                mappa[N][j] = '.';
                E++;
            }
            else{
                mappaEntities[N][j] = -1;
                mappa[N][j] = mappaTxt[j];
            }
            M = max(M, j + 1);
        }
        N++;
    }

    cout<<"Dimensioni griglia: "<<N<<" x "<<M<<"\nEntita' totali: "<<E<<" di cui "<<elfs<<" elfi e "<<ghouls<<" ghoul\n\n";
    if(DEBUGMODE){
        cout<<"=== SITUAZIONE INIZIALE ===\n";
        printMap();
        cout<<endl;
    }

    queue<int> mancanti;
    int istante = 0;
    bool anticipo = false;
    while(ghouls > 0 && elfs > 0){
        istante++;
        for(int i = 0; i < N; i++){ /// creiamo la lista di mancanti
            for(int j = 0; j < M; j++){
                if(mappaEntities[i][j] != -1)
                    mancanti.push(mappaEntities[i][j]);
            }
        }

        while(ghouls > 0 && elfs > 0 && !mancanti.empty()){
            int entita = mancanti.front();
            mancanti.pop();
            if(entities[entita].vivo && !entities[entita].attack()){ /// prova ad attaccare, se fallisce si muove
                entities[entita].muovi();
                entities[entita].attack();
            }
            if(ghouls == 0 || elfs == 0 && mancanti.size() > 0){
                cout<<"Round termina in anticipo\n";
                anticipo = true;
            }
        }
        if(DEBUGMODE){
            cout<<"After "<<istante<<" round(s)\n";
            printMap();
            cout<<"Elfs: "<<elfs<<"\tGhouls: "<<ghouls<<"\n\n\n";
            //this_thread::sleep_for(chrono::milliseconds(250));
        }
    }
    int vitaRimanente = 0;
    for(int i = 0; i < E; i++){
        if(entities[i].vivo){
            vitaRimanente+= entities[i].hp;
            //cout<<entities[i].hp<<" + ";
        }
    }
    cout<<"Outcome: "<<istante - anticipo<<" * "<<vitaRimanente<<" = "<<(istante - anticipo)*vitaRimanente<<"\n\nTermina con "<<elfs<<" elfi e "<<ghouls<<" ghoul\n";
}
