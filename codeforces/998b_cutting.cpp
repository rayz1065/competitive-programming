#include <bits/stdc++.h>
#define MAXN 105

using namespace std;
int N;
int numeri[MAXN];

int main(){
    int B;
    cin>>N>>B;

    vector<int> tagliPossibili;
    int pariinpiu = 0;
    for(int i = 0; i < N; i++){
        cin>>numeri[i];
    }
    for(int i = 0; i < N; i++){
        pariinpiu+= (numeri[i]%2)*2 - 1;
        if(pariinpiu == 0 && i + 1 < N){
            tagliPossibili.push_back(abs(numeri[i + 1] - numeri[i]));
        }
    }
    sort(tagliPossibili.begin(), tagliPossibili.end());
    int T = 0;
    for(auto i:tagliPossibili){
        B-= i;
        if(B >= 0)
            T++;
        else{
            cout<<T;
            return 0;
        }
    }
    cout<<T;
}
