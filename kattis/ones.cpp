#include <bits/stdc++.h>

using namespace std;

int main(){
    unsigned long long int S;
    int N;
    while(cin >> N){
        S = 1;
        int d = 1;
        while(S%N != 0)
            d++, S = (S%N)*10 + 1;
        cout<<d<<endl;
    }
}
