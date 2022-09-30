#include <bits/stdc++.h>

using namespace std;

int main(){
    unsigned long long int N, A, B;
    cin>>N>>A>>B;
    unsigned long long int Cmin = min(A, B), Cmax = max(A, B);
    unsigned long long int i = (N - Cmin)/Cmax;
    while(true){
        if(((N - Cmax * i) >= Cmin) ? (N - Cmax * i)%Cmin == 0 : false){
            if(A > B)
                cout<<i<<" "<<(N - Cmax * i)/Cmin;
            else
                cout<<(N - Cmax * i)/Cmin<<" "<<i;
            return 0;
        }
        i--;
    }
}
