#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n;

int padre[MAXN];

int get_padre(int a){
    if(a == padre[a]) return a;
    return padre[a] = get_padre(padre[a]);
}

void merge_set(int a, int b){
    a = get_padre(a), b = get_padre(b);
    padre[a] = b;
}

void init(){
    cin >> n;
    for(int i = 0; i <= n; i++) padre[i] = i;
}

bool get_query(char &q, int &a, int &b){
    getchar(); // endline
    q = getchar();
    if(q == '\n' || q == EOF) return false;
    cin >> a >> b;
    return true;
}

pair<int, int> solve(){
    int succ = 0, unsucc = 0;
    char q;
    int a, b;

    while(get_query(q, a, b)){
        if(q == 'c'){
            merge_set(a, b);
        }
        else if(q == 'q'){
            if(get_padre(a) == get_padre(b))
                succ++;
            else
                unsucc++;
        }
        else{
            return {succ, unsucc};
        }
    }

    return {succ, unsucc};
}

int main(){
    // fstream out;
    // out.open("output.txt", ios::out);
    int T;
    cin >> T;

    while(T--){
        init();
        pair<int, int> s = solve();
        cout<<s.first<<","<<s.second<<"\n";
        if(T) cout<<"\n";
    }
}
