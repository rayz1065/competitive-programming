#include <bits/stdc++.h>
#define MAXN 1005
using namespace std;

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

int N = 0;
struct nodeInfo{
    int x;
    int y;
    int z;
    int r;
} nodi[MAXN];

int dist(nodeInfo a, nodeInfo b){
    return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

int inRangeOf(nodeInfo a){
    int S = 0;
    for(int i = 0; i < N; i++){
        if(dist(a, nodi[i]) <= a.r){
            S++;
        }
    }
    return S;
}

int main(){
    fstream in;
    in.open("input23.txt", ios::in);

    char numeroTxt[100];
    while(in.getline(numeroTxt, 100)){
        int i = 0;
        nodi[N].x = leggiNumero(numeroTxt, i);
        nodi[N].y = leggiNumero(numeroTxt, i);
        nodi[N].z = leggiNumero(numeroTxt, i);
        nodi[N].r = leggiNumero(numeroTxt, i);
        N++;
    }

    int maxR = 0, bestNode = 0;
    for(int i = 0; i < N; i++){
        if(nodi[i].r > maxR)
            maxR = nodi[i].r, bestNode = i;
    }

    cout<<"Il nodo "<<bestNode<<" con raggio "<<maxR<<" ha "<<inRangeOf(nodi[bestNode])<<" nodi in range\n";
}
