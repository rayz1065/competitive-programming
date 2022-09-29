#include <bits/stdc++.h>
#define MOD 20183
#define XMULT 16807
#define YMULT 48271
#define MAXN 1000
using namespace std;

enum{ROCKY, WET, NARROW};
enum{NEITHER, TORCH, CLIMB_GEAR};
int depth, targetX, targetY;
long long geoIndex[MAXN][MAXN];
long long erosionLevel[MAXN][MAXN];
int mappa[MAXN][MAXN];

int leggiNumero(char stringa[], int &i){
    bool meno = false;
    int S = 0;
    while(stringa[i] != '\0' && !((stringa[i] >= '0' && stringa[i] <= '9') || stringa[i] == '-'))
        i++;
    if(stringa[i] == '-')
        meno = true, i++;
    while(stringa[i] != '\0' && ((stringa[i] >= '0' && stringa[i] <= '9')))
        S = S*10 + stringa[i++] - '0';
    return S*((meno)?-1:1);
}

void calcolaGeoIndex(){
    for(int x = 0; x < MAXN; x++){
        for(int y = 0; y < MAXN; y++){
            if(x == 0 && y == 0)
                geoIndex[x][y] = 0;
            else if(x == targetX && y == targetY)
                geoIndex[x][y] = 0;
            else if(y == 0)
                geoIndex[x][y] = x*XMULT;
            else if(x == 0)
                geoIndex[x][y] = y*YMULT;
            else
                geoIndex[x][y] = erosionLevel[x - 1][y]*erosionLevel[x][y - 1];
            erosionLevel[x][y] = (geoIndex[x][y] + depth)%MOD;
            mappa[x][y] = erosionLevel[x][y]%3;
        }
    }
}

void stampaMappa(){
    for(int y = 0; y <= targetY*2; y++){
        for(int x = 0; x <= targetX*2; x++){
            if(x == 0 && y == 0)
                cout<<"M";
            else if(x == targetX && y == targetY)
                cout<<"T";
            else if(mappa[x][y] == ROCKY)
                cout<<".";
            else if(mappa[x][y] == WET)
                cout<<"=";
            else if(mappa[x][y] == NARROW)
                cout<<"|";
        }
        cout<<endl;
    }
}

int calcolaRishio(){
    int S = 0;
    for(int x = 0; x <= targetX; x++){
        for(int y = 0; y <= targetY; y++){
            S+= mappa[x][y];
        }
    }
    return S;
}

bool visited[MAXN][MAXN][3];
int dist[MAXN][MAXN][3];
int movX[] = {-1, 0, 1, 0}, movY[] = {0, 1, 0, -1};

bool inRange(int x, int y){
    return (x >= 0 && y >= 0 && x < MAXN && y < MAXN);
}

struct posInfo{
    const int d;
    const int x;
    const int y;
    const int gear;

    int operator < (const posInfo B) const{
        return d < B.d;
    }
};

int calcolaDist(int x, int y, int gear){
    multiset<posInfo> ff;
    ff.insert({0, 0, 0, TORCH});
    for(int gear = 0; gear < 3; gear++){
        for(int x = 0; x < MAXN; x++){
            for(int y = 0; y < MAXN; y++)
                dist[x][y][gear] = INT_MAX/2;
        }
    }
    dist[x][y][gear] = 0;
    ff.insert({dist[x][y][gear], x, y, gear});

    while(!ff.empty()){
        x = ff.begin()->x, y = ff.begin()->y, gear = ff.begin()->gear;
        ff.erase(ff.begin());
        if(!visited[x][y][gear]){
            visited[x][y][gear] = true;
            int nextGear = (gear + 1)%3;
            if(nextGear == mappa[x][y])
                nextGear = (nextGear + 1)%3;
            if(dist[x][y][nextGear] > dist[x][y][gear] + 7){
                dist[x][y][nextGear] = dist[x][y][gear] + 7;
                ff.insert({dist[x][y][nextGear], x, y, nextGear});
                /*if(dist[x][y][nextGear] == 8){
                    cout<<dist[x][y][nextGear]<<" "<<x<<" "<<y<<" "<<nextGear<<endl;
                    return 0;
                }*/
            }
            for(int m = 0; m < 4; m++){
                int newx = x + movX[m], newy = y + movY[m];
                if(inRange(newx, newy) && mappa[newx][newy] != gear && dist[newx][newy][gear] > dist[x][y][gear] + 1){
                    dist[newx][newy][gear] = dist[x][y][gear] + 1;
                    /*if(dist[newx][newy][gear] == 8){
                        cout<<dist[newx][newy][gear]<<" "<<newx<<" "<<newy<<" "<<gear<<endl;
                        return 0;
                    }*/
                    int s = ff.size();
                    ff.insert({dist[newx][newy][gear], newx, newy, gear});
                }
            }
        }
    }
    return dist[targetX][targetY][TORCH];
}

int main(){
    fstream in;
    in.open("input22.txt", ios::in);

    char numeroTxt[100];
    in.getline(numeroTxt, 100);
    int i = 0;
    depth = leggiNumero(numeroTxt, i);
    in.getline(numeroTxt, 100);
    i = 0;
    targetX = leggiNumero(numeroTxt, i);
    targetY = leggiNumero(numeroTxt, i);

    calcolaGeoIndex();
    //stampaMappa();

    cout<<"Rischio = "<<calcolaRishio()<<endl;

    cout<<"Distanza = "<<calcolaDist(0, 0, TORCH)<<endl;
}
