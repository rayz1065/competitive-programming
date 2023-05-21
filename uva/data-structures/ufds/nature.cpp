#include <bits/stdc++.h>
#define MAXC 5005
#define MAXR 5005

using namespace std;

int padre[MAXC];
map<string, int> id_creature;

string creature_name[MAXC];
int c, r;

pair<int, int> relat[MAXR];

bool init(){
    cin >> c >> r;
    if(c == 0) return false;

    for(int i = 0; i < c; i++) padre[i] = i;
    id_creature.clear();

    for(int i = 0; i < c; i++){
        cin >> creature_name[i];
        id_creature[creature_name[i]] = i;
    }

    string c1, c2;
    for(int i = 0; i < r; i++){
        cin >> c1 >> c2;
        relat[i] = {id_creature[c1], id_creature[c2]};
    }

    return true;
}

int get_padre(int i){
    if(i == padre[i]) return i;
    return padre[i] = get_padre(padre[i]);
}

void join_set(int i, int j){
    int padre_i = get_padre(i), padre_j = get_padre(j);
    if(padre_i != padre_j) padre[padre_i] = padre_j;
}

bool in_same_set(int i, int j){
    return get_padre(i) == get_padre(j);
}

int count_size(int i){
    int s = 0;

    for(int j = 0; j < c; j++)
        if(in_same_set(i, j)) s++;

    return s;
}

int solve(){
    for(int i = 0; i < r; i++)
        join_set(relat[i].first, relat[i].second);

    int s = 0;

    for(int i = 0; i < c; i++)
        s = max(s, count_size(i));

    return s;
}

int main(){
    //fstream out;
    //out.open("output.txt", ios::out);

    while(init()){
        cout<<solve()<<"\n";
    }
}
