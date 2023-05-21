#include <bits/stdc++.h>
#define MAXN 10005
#define MAXL 15

using namespace std;

int n;
char numeri[MAXN][MAXL];



void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> numeri[i];
}

bool is_prefix_of(char *a, char *b){
    int i = 0;
    while(i < MAXL && a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
        i++;
    return b[i] == '\0';
}

bool solve(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            if(i != j && is_prefix_of(numeri[i], numeri[j]))
                return false;
    }
    return true;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<(solve() ? "YES" : "NO")<<"\n";
    }
}
