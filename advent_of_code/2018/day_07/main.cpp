#include <bits/stdc++.h>
#define MAXN 105
#define TEMPO_NECESSARIO 60
#define ALF 26
#define LAVORATORI 5
using namespace std;

bool arco[ALF][ALF];
vector<int> grafoReverse[ALF];
stack<int> ordine;
int visited[ALF];
int occupato[LAVORATORI];

bool avaiable(int nodo){
    for(auto i:grafoReverse[nodo])
        if(!visited[i])
            return false;
    return true;
}

bool avaiable2(int nodo, int tempo){
    for(auto i:grafoReverse[nodo])
        if(visited[i] > tempo)
            return false;
    return true;
}

void dfs(int nodo){
    visited[nodo] = true;
    for(int i = 0; i < ALF; i++){
        if(!visited[i] && avaiable(i))
            dfs(i);
    }
    ordine.push(nodo);
}

int main(){
    fstream in, out;
    in.open("input7.txt", ios::in);
    out.open("output7.txt", ios::out);

    char step[100];

    while(in.getline(step, 100)){
        arco[step[5] - 'A'][step[36] - 'A'] = true;
        grafoReverse[step[36] - 'A'].push_back(step[5] - 'A');
    }

    for(int i = 0; i < ALF; i++){
        if(!visited[i] && avaiable(i))
            dfs(i);
    }

    fill(visited, visited + ALF, 0);

    int mancanti = ALF;

    while(mancanti > 0){
        sort(occupato, occupato + LAVORATORI);

        int t = occupato[0];

        for(int i = 0; i < ALF && occupato[0] == t; i++){
            if(!visited[i] && avaiable(i) && avaiable2(i, t)){
                occupato[0] = t + i + 1 + TEMPO_NECESSARIO;
                visited[i] = occupato[0];
                cout<<t<<" -> "<<i<<" finisce a "<<occupato[0]<<endl;
                mancanti--;
            }
        }
        if(occupato[0] == t){
            occupato[0]++;
        }
    }
    cout<<*max_element(occupato, occupato + LAVORATORI);
}
