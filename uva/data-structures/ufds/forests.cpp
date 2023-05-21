#include <bits/stdc++.h>
#define MAXP 105
#define MAXT 105

using namespace std;

int p, t;
bool heard_tree[MAXP][MAXT];

int padre[MAXP];

bool get_nums(int &a, int &b){
    char c = getchar();

    if(c < '0' || c > '9') return false;

    a = b = 0;
    while(c >= '0' && c <= '9'){
        a = a * 10 + c - '0';
        c = getchar();
    }

    c = getchar();

    while(c >= '0' && c <= '9'){
        b = b * 10 + c - '0';
        c = getchar();
    }

    return true;
}

void init(){
    cin >> p >> t;
    getchar();
    memset(heard_tree, 0, sizeof(heard_tree));

    int a, b;
    while(get_nums(a, b)){
        a--, b--;
        heard_tree[a][b] = true;
    }
}

bool heard_same_trees(int i, int j){
    int k = 0;
    while(k < t && heard_tree[i][k] == heard_tree[j][k])
        k++;
    return (k == t);
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

int solve(){
    for(int i = 0; i < p; i++) padre[i] = i;

    for(int i = 0; i < p; i++){
        for(int j = i + 1; j < p; j++){
            if(!in_same_set(i, j)){
                if(heard_same_trees(i, j))
                    join_set(i, j);
            }
        }
    }

    int s = 0;
    for(int i = 0; i < p; i++)
        if(padre[i] == i) s++;
    return s;
}

int main(){
    int n;
    cin >> n;

    //fstream out;
    //out.open("output.txt", ios::out);

    while(n--){
        init();
        cout<<solve()<<"\n";
        if(n) cout<<"\n";
    }
}
