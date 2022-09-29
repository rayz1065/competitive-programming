#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin>>N;

    for(int i = 0; i < N; i++){
        int x, y;
        cin>>y>>x;

        int sq = max(x, y) - 1;
        long long S = (long long)sq * sq;
        if(sq % 2){
            // il quadrato precedente finisce in alto a destra
            S+= y;
            S+= sq - x + 1;
        }
        else{
            // il quadrato precedente finisce in basso a sinistra
            S+= x;
            S+= sq - y + 1;
        }
        cout<<S<<endl;
    }
}
