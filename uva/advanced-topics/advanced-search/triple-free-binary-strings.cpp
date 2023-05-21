#include <bits/stdc++.h>
#define MAXN 35

using namespace std;

int n;
char str[MAXN];

bool curr[MAXN];

bool isFixed(int i){
    return str[i] != '*';
}

bool init(){
    cin >> n;
    if(!n) return false;

    cin >> str;

    for(int i = 0; i < n; i++){
        if(isFixed(i))
            curr[i] = str[i] - '0';
    }

    return true;
}

bool isValid(int i){
    for(int len = 1; i - len*3 + 1 >= 0; len++){
        int b1 = i - len*3 + 1;
        int b2 = b1 + len;
        int b3 = b2 + len;

        for(int k = 0; k < len; k++){
            if(curr[b1 + k] != curr[b2 + k] || curr[b2 + k] != curr[b3 + k])
                break;
            if(k == len - 1){
                return false;
            }
        }
    }
    return true;
}

int solve(int i){
    if(i == n)
        return 1;

    if(isFixed(i)){
        if(!isValid(i))
            return 0;
        return solve(i + 1);
    }

    int s = 0;
    curr[i] = false;
    if(isValid(i))
        s+= solve(i + 1);

    curr[i] = true;
    if(isValid(i))
        s+= solve(i + 1);

    return s;
}

int solve(){
    return solve(0);
}

int main(){
    for(int i = 1; init(); i++){
        cout<<"Case "<<i<<": "<<solve()<<"\n";
    }
}
