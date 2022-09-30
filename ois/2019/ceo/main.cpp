#include <bits/stdc++.h>

using namespace std;

int N;

long long emp(int liv){
    if(liv == N)
        return 1;
    int f;
    cin >> f;
    return emp(liv + 1)*f + 1;
}

int main(){
    cin >> N;

    cout<<emp(0)<<"\n";
}