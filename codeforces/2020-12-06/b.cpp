#include <bits/stdc++.h>
#define MAXN 105
using namespace std;

int n, k;
pair<int, int> positions[MAXN];

void init(){
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> positions[i].first >> positions[i].second;
}

bool inRange(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2) <= k;
}

bool test(int x, int y){
    for(int i = 0; i < n; i++)
        if(!inRange(x, y, positions[i].first, positions[i].second)) return false;
    return true;
}


int solve(){
    for(int i = 0; i < n; i++){
        if(test(positions[i].first, positions[i].second))
            return 1;
    }
    return -1;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
