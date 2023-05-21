#include <bits/stdc++.h>
#define MAXN 40
using namespace std;

char inputTxt[100];

int adjMat[MAXN][MAXN];
int s = 0, t = 39;

int totUsers;

bool init(){
    if(!cin.getline(inputTxt, 100))
        return false;
    for(int i = 0; i < MAXN; i++)
        fill(adjMat[i], adjMat[i] + MAXN, 0);

    totUsers = 0;

    for(int i = 0; i < 10; i++)
        adjMat[27 + i][t] = 1;

    while('A' <= inputTxt[0] && inputTxt[0] <= 'Z'){
        char app = inputTxt[0];
        char users = inputTxt[1];

        adjMat[s][app - 'A' + 1] = users - '0';
        totUsers+= users - '0';

        for(int i = 3; i < 100 && inputTxt[i] != ';'; i++){
            adjMat[app - 'A' + 1][27 + inputTxt[i] - '0'] = INT_MAX>>1;
        }
        if(!cin.getline(inputTxt, 100))
            return true;
    }
    /*for(int i = 0; i < MAXN; i++){
        bool found = false;
        for(int j = 0; j < MAXN && !found; j++)
            found = (adjMat[i][j] > 0);
        if(found){
            cout<<i<<" => ";
            for(int j = 0; j < MAXN; j++){
                if(adjMat[i][j] > 0)
                    printf("%d (%d)\t", j, adjMat[i][j]);
            }
            cout<<"\n";
        }
    }*/
    return true;
}

int bfsTree[MAXN], dist[MAXN], f, mf;

bool findAugPath(int nodo){
    queue<int> FF;
    FF.push(nodo);

    fill(bfsTree, bfsTree + MAXN, -1);
    fill(dist, dist + MAXN, INT_MAX>>1);
    f = INT_MAX>>1;

    dist[nodo] = 0;

    while(!FF.empty()){
        nodo = FF.front();
        FF.pop();

        if(nodo == t){
            while(!FF.empty())
                FF.pop();
            return true;
        }

        for(int i = 0; i < MAXN; i++){
            if(adjMat[nodo][i] > 0 && dist[i] == INT_MAX>>1){
                dist[i] = dist[nodo] + 1;
                bfsTree[i] = nodo;
                FF.push(i);
            }
        }
    }
    return false;
}

void augment(int nodo){
    if(bfsTree[nodo] != -1){
        f = min(f, adjMat[bfsTree[nodo]][nodo]);
        augment(bfsTree[nodo]);

        adjMat[bfsTree[nodo]][nodo]-= f;
        adjMat[nodo][bfsTree[nodo]]+= f;
    }
}

void computeMaxFlow(){
    mf = 0;
    while(true){
        if(!findAugPath(s))
            break ;
        augment(t);
        mf+= f;
    }
}

int main(){
    FILE *out = stdout;

    while(init()){
        computeMaxFlow();
        if(mf < totUsers)
            fprintf(out, "!\n");
        else{
            for(int i = 27; i < 37; i++){
                bool found = false;
                for(int j = 1; j < 27; j++){
                    if(adjMat[i][j] == 1)
                        found = true, fprintf(out, "%c", j + 'A' - 1);
                }
                if(!found)
                    fprintf(out, "_");
            }
            fprintf(out, "\n");
        }
    }
}
