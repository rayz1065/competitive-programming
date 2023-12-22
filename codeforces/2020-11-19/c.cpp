#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;

int n;
char str[MAXN];

void init(){
    cin >> str;
    n = strlen(str);
}

int solve(){
    int openingP = 0, openingS = 0, am = 0;

    for(int i = 0; i < n; i++){
        if(str[i] == '(')
            openingP++;
        if(str[i] == '[')
            openingS++;
        if(str[i] == ')' && openingP > 0)
            openingP--, am++;
        if(str[i] == ']' && openingS > 0)
            openingS--, am++;
    }

    return am;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
