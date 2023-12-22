#include <bits/stdc++.h>

using namespace std;

int main(){
    int l, r;
    cin >> l >> r;

    if(l == 0 && r == 0)
        cout<<"Not a moose";
    else if(l == r)
        cout<<"Even "<<l*2;
    else if(l > r)
        cout<<"Odd "<<l*2;
    else
        cout<<"Odd "<<r*2;
}
