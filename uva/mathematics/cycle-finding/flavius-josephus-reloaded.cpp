#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> found;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, a, b;
    cin>>N;
    while(N != 0){
        cin>>a>>b;
        int surv = N, soldato = 0;
        found.clear();

        while(surv > 0 && found[soldato] < 2){
            found[soldato]++;
            if(found[soldato] == 2)
                surv--;
            soldato = (((((long long)a)*soldato)%N)*soldato + b)%N;
        }
        cout<<surv<<endl;

        cin>>N;
    }
}
