#include <bits/stdc++.h>
#define MAXN 10

using namespace std;

int n, m;
const int patternSize = 3;

bool grid[MAXN][MAXN];
bool pattern[patternSize][patternSize];
char patternStr[patternSize + 2][patternSize + 2];

int minSol;
vector<int> bestSol;
vector<int> currSol;

bool init(){
    cin >> n >> m;
    if(n == 0) return false;

    for(int i = 0; i < patternSize; i++)
        cin >> patternStr[i];

    for(int r = 0; r < 3; r++)
        for(int c = 0; c < 3; c++)
            pattern[r][c] = patternStr[r][c] == '*';

    for(int r = 0; r < n; r++)
        for(int c = 0; c < m; c++)
            grid[r][c] = true;

    bestSol.clear();
    currSol.clear();
    minSol = INT_MAX >> 1;

    return true;
}

bool solvedUpTo(int r){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < m; j++)
            if(grid[i][j])
                return false;
    }
    return true;
}

bool inRange(int r, int c){
    return r >= 0 && c >= 0 && r < n && c < m;
}

int getNum(int r, int c){
    return r*m + c + 1;
}

void press(int r, int c){
    if(!currSol.empty() && currSol[currSol.size() - 1] == getNum(r, c))
        currSol.pop_back();
    else
        currSol.push_back(getNum(r, c));

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            int newr = r + i - 1, newc = c + j - 1;
            if(inRange(newr, newc))
                grid[newr][newc]^= pattern[i][j];
        }
    }
}

void solve(int r, int c){
    if(currSol.size() >= minSol) return ;

    if(c == m) c = 0, r++;
    if(r == n){
        if(solvedUpTo(n)){
            bestSol = currSol;
            minSol = currSol.size();
        }
        return ;
    }
    if(!solvedUpTo(r - 1)) return ;

    solve(r, c + 1);
    press(r, c);
    solve(r, c + 1);
    press(r, c);
}

bool solve(){
    solve(0, 0);
    if(minSol == INT_MAX >> 1)
        return false;
    return true;
}

bool isRightSolution(){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            grid[i][j] = true;

    for(auto o:bestSol){
        press((o - 1)/m, (o - 1)%m);
    }
    return solvedUpTo(n);
}

int main(){
    for(int t = 1; init(); t++){
        cout<<"Case #"<<t<<"\n";
        if(solve()){
            bool f = true;
            for(auto i:bestSol){
                if(!f) cout<<" ";
                f = false;
                cout<<i;

                // assert(isRightSolution());
            }
        }
        else{
            cout<<"Impossible.";
        }
        cout<<"\n";
    }
}
