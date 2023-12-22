#include <bits/stdc++.h>

using namespace std;

int prob[105];

int main(){
    int n;
    cin >> n;
    int s = 0;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        s+= (a < 0);
    }
    cout<<s<<"\n";
}
