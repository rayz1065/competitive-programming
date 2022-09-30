#include <bits/stdc++.h>

using namespace std;

int main(){
    long long R, C;
    cin>>R>>R>>C;

    cout<<(R * (R+1))/2 - ((R - C) * (R - C + 1))/2 - ((C - 1) * C)/2;
}
