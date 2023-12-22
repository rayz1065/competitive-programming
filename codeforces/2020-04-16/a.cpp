#include <bits/stdc++.h>
#define MAXN 105
using namespace std;

int n;

pair<int, int> plays[MAXN];

bool solve(){
    pair<int, int> lastS = {0, 0};
    for(int i = 0; i < n; i++){
        if(plays[i].first < lastS.first)
            return false;
        if(plays[i].first - plays[i].second < lastS.first - lastS.second)
            return false;
        if(plays[i].second < lastS.second)
            return false;
        lastS = plays[i];
    }
    return true;
}

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> plays[i].first >> plays[i].second;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<((solve()) ? "YES" : "NO")<<"\n";
    }
}
