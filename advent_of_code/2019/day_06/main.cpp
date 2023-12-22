#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <queue>

#define MAXN 1500
#define MAXL 10

using namespace std;

map<string, int> pianeti;
string nome_pianeta[MAXN];
vector<int> grafo[MAXN];
int adj_mat[MAXN][MAXN];
int padre[MAXN];

char input[MAXL];
int n_pianeti = 0;

int get_pianeta(string p){
    if(pianeti.count(p) == 0){
        pianeti[p] = n_pianeti;
        nome_pianeta[n_pianeti++] = p;
    }
    return pianeti[p];
}

void aggiungi_arco(int p, int f){
    adj_mat[p][f] = 1;
    adj_mat[f][p] = 1;
    grafo[p].push_back(f);
    grafo[f].push_back(p);
    padre[p] = f;
}

void fill_adj_mat(){
    for(int k = 0; k < n_pianeti; k++)
        for(int i = 0; i < n_pianeti; i++)
            for(int j = 0; j < n_pianeti; j++)
                    adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);
}

int dist[MAXN];

int get_dist(string da, string a){
    int p1 = get_pianeta(da), p2 = get_pianeta(a);
    queue<int> ff;
    ff.push(p1);
    fill(dist, dist + MAXN, MAXN >> 1);
    dist[p1] = 0;

    while(!ff.empty()){
        int nodo = ff.front();
        ff.pop();

        for(auto i:grafo[nodo])
            if(dist[nodo] + 1 < dist[i])
                dist[i] = dist[nodo] + 1, ff.push(i);
    }

    return dist[p2] - 2;
}

bool interpreta_riga(){
    cin.getline(input, MAXL);
    string n1, n2;

    int i;
    for(i = 0; i < MAXL && input[i] != '\0' && input[i] != ')'; i++)
        n1.push_back(input[i]);
    if(i >= MAXL || input[i] == '\0')
        return false;

    for(i = i + 1; i < MAXL && input[i] != '\0'; i++)
        n2.push_back(input[i]);
    if(i >= MAXL || input[i] != '\0')
        return false;

    int p1 = get_pianeta(n1), p2 = get_pianeta(n2);
    aggiungi_arco(p2, p1);
    return true;
}

void interpreta_input(){
    memset(adj_mat, 1, sizeof(adj_mat));
    fill(padre, padre + MAXN, -1);
    while(interpreta_riga());
}

int get_orbits(int p){
    if(padre[p] == -1)
        return 0;
    return get_orbits(padre[p]) + 1;
}

int parte_1(){
    int s = 0;
    for(int i = 0; i < n_pianeti; i++)
        s+= get_orbits(i);
    return s;
}

int parte_2(){
    return get_dist("YOU", "SAN");
}

int main(){
    interpreta_input();
    printf("pianeti: %d\n", n_pianeti);

    printf("parte 1: %d\n", parte_1());
    printf("parte 2: %d\n", parte_2());
}
