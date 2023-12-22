#include <bits/stdc++.h>
#define MAXN 300005

using namespace std;

int n;
int numb[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        numb[i] = i + 1;
}

bool can_solve(vector<int> p, vector<int> &s){
    if(p.size() == 1)
        return true;

    for(auto j:p)
        cout<<j<<" ";
    cout<<"\n";

    for(int i = 0; i < p.size(); i++){
        if((i - 1 >= 0 && p[i - 1] < p[i]) || (i + 1 < p.size() && p[i] < p[i + 1])){
            int removed = p[i];

            vector<int> tmp;
            for(auto j:p){
                if(j != removed)
                    tmp.push_back(j);
            }
            s.push_back(removed);
            if(can_solve(tmp, s))
                return true;
            s.pop_back();
        }
    }
    return false;
}

void solve(){
    do{
        vector<int> tmp;
        vector<int> sol;

        for(int i = 0; i < n; i++)
            cout<<numb[i]<<" ";
        cout<<"\n";
        for(int i = 0; i < n; i++)
            tmp.push_back(numb[i]);

        if(can_solve(tmp, sol)){
            cout<<"YES\n";
            for(auto j:sol)
                cout<<j<<" ";
            cout<<"\n\n------------------\n\n";
        }
        else
            cout<<"NO\n\n------------------\n\n";

    } while(next_permutation(numb, numb + n));
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
    }
}
