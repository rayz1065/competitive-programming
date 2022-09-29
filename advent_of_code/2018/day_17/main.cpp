#include <bits/stdc++.h>
#define MAXN 5000
using namespace std;

fstream out;
int yMax = 1, yMin = INT_MAX, xMin = 500, xMax = 500;
int mappa[MAXN][MAXN];

char deco[] = ".#|~+";
enum{SAND, CLAY, FLOW, WATER, SORGENTE};

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

int contaAcqua(){
    int S = 0;
    for(int y = yMin; y <= yMax; y++){
        for(int x = xMin; x <= xMax; x++){
            S+= (mappa[x][y] == FLOW || mappa[x][y] == WATER);
        }
    }
    return S;
}

int contaAcquaStill(){
    int S = 0;
    for(int y = yMin; y <= yMax; y++){
        for(int x = xMin; x <= xMax; x++){
            S+= (mappa[x][y] == WATER);
        }
    }
    return S;
}

void stampaMappa(){
    for(int y = yMin; y <= yMax; y++){
        for(int x = xMin; x <= xMax; x++){
            out<<deco[mappa[x][y]]<<" ";
        }
        out<<endl;
    }
    out<<endl;
}

void stillW(int x, int y){
    if(x > xMax || x < xMin || y > yMax)
        return ;
    if(mappa[x][y] == FLOW)
        mappa[x][y] = WATER;
    if(mappa[x + 1][y] == FLOW)
        stillW(x + 1, y);
    if(mappa[x - 1][y] == FLOW)
        stillW(x - 1, y);
}

int versa(int x, int y){
    if(x > xMax || x < xMin || y > yMax)
        return 0;
    if(mappa[x][y + 1] == SAND){
        mappa[x][y + 1] = FLOW;
        versa(x, y + 1);
    }
    if(mappa[x][y + 1] == CLAY || mappa[x][y + 1] == WATER){
        int enc = 0;
        if(mappa[x + 1][y] == SAND){
            mappa[x + 1][y] = FLOW;
            enc+= versa(x + 1, y);
        }
        else if(mappa[x + 1][y] == CLAY || mappa[x + 1][y] == WATER)
            enc++;
        if(mappa[x - 1][y] == SAND){
            mappa[x - 1][y] = FLOW;
            enc+= versa(x - 1, y);
        }
        else if(mappa[x - 1][y] == CLAY || mappa[x - 1][y] == WATER)
            enc++;
        if(enc == 2){
            stillW(x, y);
        }
        return enc;
    }
    return 0;
}

int main(){
    fstream in;
    in.open("input17.txt", ios::in);
    out.open("output17.txt", ios::out);

    char inputTxt[100];
    while(in.getline(inputTxt, 100)){
        int i = 0, a, b, c;
        a = leggiNumero(inputTxt, i);
        b = leggiNumero(inputTxt, i);
        c = leggiNumero(inputTxt, i);
        assert(c < MAXN && b >= 0);
        if(b > c)
            swap(b, c);
        if(inputTxt[0] == 'y'){
            yMax = max(yMax, a);
            yMin = min(yMin, a);
            xMax = max(xMax, c);
            xMin = min(xMin, b);
            for(int x = b, y = a; x <= c; x++)
                mappa[x][y] = CLAY;
        }
        else if(inputTxt[0] == 'x'){
            yMax = max(yMax, c);
            yMin = min(yMin, b);
            xMax = max(xMax, a);
            xMin = min(xMin, a);
            for(int x = a, y = b; y <= c; y++)
                mappa[x][y] = CLAY;
        }
        else
            assert(false);
    }
    mappa[500][0] = SORGENTE;
    xMin--;
    xMax++;

    versa(500, 0);
    stampaMappa();

    cout<<contaAcqua()<<endl<<contaAcquaStill();
}
