#include <bits/stdc++.h>

using namespace std;

unordered_map<int, int> ultimaVolta;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin>>N;

    int curr = 0, lastSep = -1, S = 0;
    for(int i = 0; i < N; i++){
        int a;
        cin>>a;
        if(ultimaVolta.count(a) && ultimaVolta[a] > lastSep)
            lastSep = ultimaVolta[a];
        ultimaVolta[a] = i;
        S = max(S, i - lastSep);
    }
    cout<<S;
}
