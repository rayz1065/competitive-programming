#include <bits/stdc++.h>

using namespace std;

int main(){
    int w, n;
    cin >> w >> n;

    long long int area = 0;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        area+= a * b;
    }

    cout<<area/w<<"\n";
}
