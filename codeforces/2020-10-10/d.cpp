#include <bits/stdc++.h>
#define MAXN 55

using namespace std;

int n;
vector<int> curr;

void init(){
    cin >> n;
    curr.resize(n);
    for(int i = 0; i < n; i++)
        cin >> curr[i];
}

vector<int> performPermut(vector<int> permut){
    vector<vector<int>> raccolti(permut.size());
    int i = 0;
    for(int j = 0; j < permut.size(); j++){
        for(int k = 0; k < permut[j]; k++){
            raccolti[j].push_back(curr[i++]);
        }
    }

    reverse(raccolti.begin(), raccolti.end());

    vector<int> s;

    for(int j = 0; j < permut.size(); j++){
        for(auto a: raccolti[j]){
            s.push_back(a);
        }
    }

    return s;
}

void genAllPermut(vector<int> &currPermut, int s){
    if(s == n){
        vector<int> a = performPermut(currPermut);
        for(auto i:currPermut)
            cout<<i<<" ";
        cout<<"\n";
        for(auto i:a)
            cout<<i<<" ";
        cout<<"\n\n";
        return ;
    }
    for(int j = 1; s + j <= n; j++){
        currPermut.push_back(j);
        genAllPermut(currPermut, s + j);
        currPermut.pop_back();
    }
}

int main(){
    init();
    vector<int> tmp;
    genAllPermut(tmp, 0);
}
