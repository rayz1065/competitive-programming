#include <bits/stdc++.h>
#define MAXN 500005

using namespace std;

int n, b;
int pop[MAXN];
int assigned[MAXN];
multiset<pair<int, int>> valori;

bool init(){
    cin >> n >> b;
    if(n == -1)
        return false;
    for(int i = 0; i < n; i++)
        cin >> pop[i];
    fill(assigned, assigned + n, 1);
    b-= n;
    valori.clear();
    return true;
}

int getCost(int i){
    if(pop[i]%assigned[i] == 0)
        return pop[i]/assigned[i];
    return pop[i]/assigned[i] + 1;
}

int main(){
    while(init()){
        for(int i = 0; i < n; i++){
            valori.insert({-getCost(i), i});
        }
        while(b--){
            int i = valori.begin()->second;
            valori.erase(valori.begin());
            assigned[i]+= 1;
            valori.insert({-getCost(i), i});
        }
        cout<<getCost(valori.begin()->second)<<"\n";
    }
}
