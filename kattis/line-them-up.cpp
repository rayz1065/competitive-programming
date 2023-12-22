#include <bits/stdc++.h>

using namespace std;

int n;

int main(){
    cin >> n;
    string lst;
    cin >> lst;

    bool decreasing = true;
    bool increasing = true;

    for(int i = 0; i < n - 1; i++){
        string curr;
        cin >> curr;
        if(lst < curr)
            decreasing = false;
        if(lst > curr)
            increasing = false;
        lst = curr;
    }

    if(decreasing) cout<<"DECREASING\n";
    else if(increasing) cout<<"INCREASING\n";
    else cout<<"NEITHER\n";
}
