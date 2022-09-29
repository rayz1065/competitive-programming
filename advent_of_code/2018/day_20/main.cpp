#include <bits/stdc++.h>
#define MAXL 15000
#define MAXN 250
using namespace std;

fstream out;

char reg[MAXL];
char mappa[MAXN][MAXN];
bool visited[MAXN][MAXN];
int dist[MAXN][MAXN];

int xMax = MAXN/2, yMax = MAXN/2, xMin = MAXN/2, yMin = MAXN/2;
int movX[] = {-1, 0, 1, 0}, movY[] = {0, 1, 0, -1};
enum{NORD, EST, SUD, OVEST};

inline bool isDire(char c){
    return (c == 'E' || c == 'W' || c == 'N' || c == 'S');
}

inline int getDire(char c){
    if(c == 'N')
        return NORD;
    if(c == 'E')
        return EST;
    if(c == 'S')
        return SUD;
    if(c == 'W')
        return OVEST;
    assert(false);
}

void stampaMappa(){
    for(int x = xMin - 1; x <= xMax + 1; x++){
        for(int y = yMin - 1; y <= yMax + 1; y++)
            out<<mappa[x][y];
        out<<"\n";
    }
    out<<"\n";
}

void esplora(int x, int y){
    stack<pair<int, int> > m;
    for(int i = 1; i < MAXL && reg[i] != '\0'; i++){
        if(isDire(reg[i])){
            int d = getDire(reg[i]);
            x+= movX[d], y+= movY[d];
            if(d == NORD || d == SUD)
                mappa[x][y] = '-';
            else
                mappa[x][y] = '|';
            x+= movX[d], y+= movY[d];
            mappa[x][y] = '.';
        }
        else if(reg[i] == '(')
            m.push({x, y});
        else if(reg[i] == ')')
            m.pop();
        else if(reg[i] == '|')
            x = m.top().first, y = m.top().second;
        xMin = min(x, xMin);
        xMax = max(x, xMax);
        yMin = min(y, yMin);
        yMax = max(y, yMax);
    }
}

bool inRange(int x, int y){
    return (x >= xMin && x <= xMax && y >= yMin && y <= yMax);
}

void calcolaDist(int x, int y){
    queue<pair<int, int> > ff;
    ff.push({x, y});
    visited[x][y] = true;
    dist[x][y] = 0;

    while(!ff.empty()){
        x = ff.front().first, y = ff.front().second;
        ff.pop();
        for(int m = 0; m < 4; m++){
            int newX = x + movX[m], newY = y + movY[m];
            //cout<<newX<<" "<<newY<<" -> inRange(newX, newY) "<<inRange(newX, newY)<<" !visited[newX][newY] "<<(!visited[newX][newY])<<" mappa[newX][newY] != '#' "<<(mappa[newX][newY] != '#')<<endl;
            if(inRange(newX, newY) && !visited[newX][newY] && mappa[newX][newY] != '#'){
                visited[newX][newY] = true;
                newX+= movX[m], newY+= movY[m];
                dist[newX][newY] = dist[x][y] + 1;
                visited[newX][newY] = true;
                ff.push({newX, newY});
            }
        }
    }
}

int getMaxDist(){
    int maxDist = 0;

    for(int x = xMin; x <= xMax; x++){
        for(int y = yMin; y <= yMax; y++)
            maxDist = max(maxDist, dist[x][y]);
    }
    return maxDist;
}

int getDistAtLeast(int distM){
    int S = 0;

    for(int x = xMin; x <= xMax; x++){
        for(int y = yMin; y <= yMax; y++)
            S+= (dist[x][y] >= distM);
    }
    return S;
}

int main(){
    fstream in;
    in.open("input20.txt", ios::in);
    out.open("output20.txt", ios::out);

    int N = 0;
    in.getline(reg, MAXL);
    memset(mappa, '#', sizeof(char)*MAXN*MAXN);

    mappa[MAXN/2][MAXN/2] = 'X';
    esplora(MAXN/2, MAXN/2);
    stampaMappa();
    calcolaDist(MAXN/2, MAXN/2);
    cout<<"Distanza massima = "<<getMaxDist()<<"\n";
    cout<<"Stanze a distanza 1000 = "<<getDistAtLeast(1000)<<"\n";
}
