#include <bits/stdc++.h>

using namespace std;

string tent;
int corr, place, S;

void init(){
    S = 0;
    cin >> tent >> corr >> place;
}

pair<int, int> compara(string A, string B){
    pair<int, int> S = {0, 0};
    bool usedA[A.length()] = {}, usedB[B.length()] = {};

    for(int i = 0; i < A.length(); i++){
        if(A[i] == B[i])
            S.first++, usedA[i] = usedB[i] = true;
    }

    for(int i = 0; i < A.length(); i++){
        for(int j = 0; !usedA[i] && j < B.length(); j++){
            if(!usedB[j] && A[i] == B[j])
                S.second++, usedA[i] = usedB[j] = true;
        }
    }
    return S;
}

void solve(string curr){
    if(curr.length() == tent.length()){
        auto t = compara(tent, curr);
        if(t.first == corr && t.second == place)
            S++;
        return ;
    }
    for(int i = 1; i <= 9; i++){
        curr.push_back(i + '0');
        solve(curr);
        curr.pop_back();
    }
}

int solve(){
    solve("");
    return S;
}

int main(){
    FILE *out = stdout;

    int N;
    cin >> N;

    for(int t = 1; t <= N; t++){
        init();
        fprintf(out, "%d\n", solve());
    }
}
