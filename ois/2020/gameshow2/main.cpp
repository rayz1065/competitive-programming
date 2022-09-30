#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int v[MAXN], p[MAXN], c[MAXN];

int main(){
    cin >> n;

    for(int i = 0; i < n; i++)
        cin >> v[i];
    for(int i = 0; i < n; i++)
        cin >> p[i];
    for(int i = 0; i < n; i++)
        cin >> c[i];

    int budget = 0, money = 0, prices = 0;
    for(int i = 0; i < n; i++){
        if(v[i] - p[i] > c[i]){
            prices+= v[i];
            if(money < p[i])
                budget+= p[i] - money, money+= p[i] - money; // money = p[i]

            money-= p[i];
        }
        else{
            money+= c[i];
        }
    }

    cout<<money + prices - budget<<" "<<budget<<"\n";
}
