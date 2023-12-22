#include <bits/stdc++.h>

using namespace std;

int prob[45];

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            prob[i + j]+= 1;
        }
    }
    int mx = *max_element(prob, prob + 45);
    for(int i = 0; i < 40; i++){
        if(prob[i] == mx){
            cout<<i<<"\n";
        }
    }
}
