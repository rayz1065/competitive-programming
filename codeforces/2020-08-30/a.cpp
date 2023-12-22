#include <bits/stdc++.h>
#define MAXN 1005
#define MAXS 1005
#define ALF 30
using namespace std;

int n;

char strings[MAXN][MAXS];
int freq[ALF];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> strings[i];
    memset(freq, 0, sizeof freq);
}

bool solve(){
    for(int i = 0; i < n; i++){
        int j = 0;
        while(strings[i][j] != '\0'){
            freq[strings[i][j] - 'a']++;
            j++;
        }
    }

    for(int i = 0; i < ALF; i++){
        if(freq[i]%n != 0)
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
