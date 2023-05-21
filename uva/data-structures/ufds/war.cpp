#include <bits/stdc++.h>
#define MAXP 10005
#define MAXN (MAXP*2 + 5)
#define ENEMY(x) (x + MAXP)

using namespace std;

int n, m;

int padre[MAXN];

int get_padre(int nodo){
    if(nodo == padre[nodo]) return nodo;
    return padre[nodo] = get_padre(padre[nodo]);
}

void join_set(int a, int b){
    a = get_padre(a), b = get_padre(b);
    if(a != b) padre[a] = b;
}

bool is_same_set(int a, int b){
    return get_padre(a) == get_padre(b);
}

bool are_friends(int a, int b){
    return is_same_set(a, b);
}

bool are_enemies(int a, int b){
    return is_same_set(a, ENEMY(b));
}

bool set_friends(int a, int b){
    if(are_enemies(a, b))
        return false;

    join_set(a, b);
    join_set(ENEMY(a), ENEMY(b));
    return true;
}

bool set_enemies(int a, int b){
    if(are_friends(a, b))
        return false;

    join_set(a, ENEMY(b));
    join_set(ENEMY(a), b);
    return true;
}

void init(){
    cin >> n;
    for(int i = 0; i < MAXN; i++)
        padre[i] = i;
}

bool read_op(int &op, int &a, int &b){
    cin >> op >> a >> b;
    return (op != 0);
}

void solve(){
    // fstream out;
    // out.open("output.txt", ios::out);

    int op, a, b;
    while(read_op(op, a, b)){
        if(op == 1){
            if(!set_friends(a, b)) cout<<-1<<"\n";
        }
        else if(op == 2){
            if(!set_enemies(a, b)) cout<<-1<<"\n";
        }
        else if(op == 3){
            cout<<are_friends(a, b)<<"\n";
        }
        else if(op == 4){
            cout<<are_enemies(a, b)<<"\n";
        }
    }
}

int main(){
    init();
    solve();
}
