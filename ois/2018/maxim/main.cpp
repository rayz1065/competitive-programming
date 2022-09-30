#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int N, K, prezzo;
    cin>>N>>K;
    queue<int> regali;
    multiset<int> prezzi;
    for(int i = 0; i <=K; i++){
        cin>>prezzo;
        regali.push(prezzo);
        prezzi.insert(prezzo);
    }
    int maxS = 0;
    for(int i = K + 1; i < N; i++){
        maxS = max(maxS, abs(*prezzi.begin() - *prezzi.rbegin()));
        cin>>prezzo;
        prezzi.erase(prezzi.find(regali.front()));
        regali.pop();
        regali.push(prezzo);
        prezzi.insert(prezzo);
    }
    cout<<max(maxS, abs(*prezzi.begin() - *prezzi.rbegin()));
}
