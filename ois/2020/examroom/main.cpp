#include <iostream>

using namespace std;

int main(){
    long long int r, c, k;
    cin >> r >> c >> k;
    cout<<((r + k - 1)/k) * ((c + k - 1)/k)<<"\n";
}
