#include <bits/stdc++.h>
#define MAXN 400
#define MAX_SIZE 200
using namespace std;

bool matCielo[MAX_SIZE][MAX_SIZE];

struct segnale{
    int x;
    int y;
    int vx;
    int vy;
} listaSegnali[MAXN];

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

int main(){
    fstream in, out;
    in.open("input10.txt", ios::in);
    out.open("output10_messaggio.txt", ios::out);

    char infoSegnale[100];
    int N = 0;
    while(in.getline(infoSegnale, 100)){
        int i = 0;
        listaSegnali[N].x = leggiNumero(infoSegnale, i);
        listaSegnali[N].y = leggiNumero(infoSegnale, i);
        listaSegnali[N].vx = leggiNumero(infoSegnale, i);
        listaSegnali[N].vy = leggiNumero(infoSegnale, i);
        N++;
    }

    for(int t = 10009; t < 10010; t++){
        int xMax = 0, yMax = 0, xMin = INT_MAX, yMin = INT_MAX;
        for(int c = 0; c < N; c++){
            int x = listaSegnali[c].x + listaSegnali[c].vx * t;
            int y = listaSegnali[c].y + listaSegnali[c].vy * t;
            if(x >= 0 && y >= 0 && x < MAX_SIZE && y < MAX_SIZE)
                matCielo[x][y] = true;
            xMax = max(xMax, x);
            yMax = max(yMax, y);
            xMin = min(xMin, x);
            yMin = min(yMin, y);
        }
        out<<"T = "<<t<<" x da "<<xMin<<" a "<<xMax<<", y da "<<yMin<<" a "<<yMax<<endl;
        for(int j = yMin; j <= yMax && j < MAX_SIZE; j++){
            for(int x = xMin; x <= xMax && x < MAX_SIZE; x++)
                out<<((matCielo[x][j])?'#':'.')<<" ";
            out<<endl;
        }
        out<<endl;
        for(int j = 0; j < MAX_SIZE; j++){
            for(int x = 0; x < MAX_SIZE; x++)
                matCielo[x][j] = false;
        }
    }
}
