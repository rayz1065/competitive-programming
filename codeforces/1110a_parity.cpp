#include <bits/stdc++.h>

using namespace std;

int main(){
    int b, k;
    cin >> b >> k;

    bool isEven = true;

    int ai;
    for(int i = k - 1; i >= 0; i--){
        cin >> ai;
        ai%= 2;
        if(isEven && ai%2)
            isEven = false;
        else if(!isEven && ai%2)
            isEven = true;
    }
    if(b%2)
        cout<<((isEven)?"even":"odd");
    else
        cout<<((ai%2)?"odd":"even");
}
