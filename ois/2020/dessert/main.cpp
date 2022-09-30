#include <bits/stdc++.h>
#define MAXN 300005

using namespace std;

int n;
int req[MAXN];
vector<int> friendof[MAXN];
queue<int> ff;

void take_dessert(int i){
    for(auto j:friendof[i]){
        req[j]--;
        if(req[j] == 0)
            ff.push(j);
    }
}

bool iter(){
    if(ff.empty())
        return false;
    take_dessert(ff.front());
    ff.pop();
    return true;
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++){
        int m;
        cin >> m >> req[i];
        while(m--){
            int a;
            cin >> a;
            friendof[a].push_back(i);
        }
    }

    for(int i = 0; i < n; i++){
        if(req[i] == 0)
            ff.push(i);
    }

    int s = 0;
    while(iter())
        s++;
    cout<<s<<"\n";
}
