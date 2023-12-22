#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n;
bool a[MAXN];
vector<int> bestSol;

bool solved[MAXN][MAXN*2];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    bestSol.clear();
    memset(solved, 0, sizeof solved);
}

void solve(int i, int oddMoreThanEven, vector<int> &sol){
    if(i == n){
        if(oddMoreThanEven == 0 && sol.size() > bestSol.size()){
            bestSol.clear();
            for(auto a:sol)
                bestSol.push_back(a);
        }
        return ;
    }
    if(solved[i][oddMoreThanEven + MAXN]) return ;
    solved[i][oddMoreThanEven + MAXN] = true;

    int currIdx = sol.size();
    if(currIdx%2){
        sol.push_back(a[i]);
        solve(i + 1, oddMoreThanEven - a[i], sol);
        sol.pop_back();
        solve(i + 1, oddMoreThanEven, sol);
    }
    else{
        sol.push_back(a[i]);
        solve(i + 1, oddMoreThanEven + a[i], sol);
        sol.pop_back();
        solve(i + 1, oddMoreThanEven, sol);
    }
}

int main(){
    int t;
    cin >> t;

    while(t--){
        vector<int> tmp;
        init();
        solve(0, 0, tmp);

        cout<<bestSol.size()<<"\n";
        for(auto i:bestSol)
            cout<<i<<" ";
        if(bestSol.size() > 0)
            cout<<"\n";
    }
}
