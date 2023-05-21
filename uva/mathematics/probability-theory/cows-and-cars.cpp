#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int main(){
    int A, B, C;

    while(cin >> C >> A >> B){
        int T = A + C, newT = T - B;

        double carp = (double)A/T, cowp = (double)C/T;
        double ifcow = cowp*A/(newT - 1), ifcar = carp*(A - 1)/(newT - 1);
        double S = ifcow + ifcar;

        printf("%.5f\n", S);//cout<<S<<"\n";
    }
}
