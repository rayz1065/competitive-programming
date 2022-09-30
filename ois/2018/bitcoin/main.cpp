#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int N, E;
    cin>>N>>E;
    int delta;

    double S = 0, btc = 1;
    for(int i = 0; i < N; i++){
        cin >> delta;
        if(delta < 0 && S == 0){
            S = E*btc;
            btc = 0;
        }
        else if(delta > 0 && btc == 0){
            btc = S/E;
            S = 0;
        }

        E+= delta;
    }
    S+= E * btc;
    cout.precision(log10(S) + 7);
    cout<<S;
}
