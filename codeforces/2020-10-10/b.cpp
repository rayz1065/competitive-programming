#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n, k;
char games[MAXN];
int gamesChanged;

void init(){
    cin >> n >> k;
    cin >> games;
    gamesChanged = 0;
}

void changeGames(int dist){
    for(int i = 1; i < n; i++){
        if(games[i] == 'L' && games[i - 1] == 'W' && i + dist < n && games[i + dist] == 'W'){
            for(int j = i; j < i + dist && gamesChanged < k; j++){
                assert(games[i] == 'L');
                gamesChanged++;
                games[i] = 'W';
            }
        }
    }
}

int calcScore(){
    // cout<<"chosen: "<<games<<" -> "<<gamesChanged<<"\n";
    int s = (games[0] == 'W');
    for(int i = 1; i < n; i++){
        if(games[i] == 'W'){
            s+= 1 + (games[i - 1] == 'W');
        }
    }
    return s;
}

int solve(){
    int firstWin = 0;
    while(firstWin < n && games[firstWin] == 'L')
        firstWin++;

    if(firstWin == n){
        for(int i = 0; i < k; i++)
            games[i] = 'W', gamesChanged++;
        return calcScore();
    }

    int lastWin = n - 1;
    while(lastWin >= 0 && games[lastWin] == 'L')
        lastWin--;


    vector<pair<int,int>> distances;
    int lastW = firstWin;
    for(int i = firstWin; i < n; i++){
        if(games[i] == 'W'){
            if(lastW >= 0 && i - lastW - 1 > 0)
                distances.push_back({i - lastW - 1, i});
            lastW = i;
        }
    }

    sort(distances.begin(), distances.end());

    for(auto i:distances){
        // cout<<i.first<<"\t"<<i.second<<"\n";
        int idx = i.second, len = i.first;
        for(int j = idx - 1; j >= idx - len && gamesChanged < k; j--){
            // cout<<"len = "<<len<<", idx = "<<idx<<"\t"<<games[j]<<" "<<j<<"\n";
            assert(games[j] == 'L');
            games[j] = 'W';
            gamesChanged++;
            // cout<<"len = "<<len<<", idx = "<<idx<<"\t"<<games[j]<<" "<<j<<"\n";
        }
    }

    if(gamesChanged < k){
        for(int i = firstWin - 1; i >= 0 && gamesChanged < k; i--){
            games[i] = 'W', gamesChanged++;
        }
    }

    if(gamesChanged < k){
        for(int i = lastWin + 1; i < n && gamesChanged < k; i++){
            games[i] = 'W', gamesChanged++;
        }
    }

    return calcScore();
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
