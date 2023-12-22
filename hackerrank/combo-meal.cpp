#include <bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    for(int c = 0; c < T; c++){
        int a, b, ab;
        cin>>a>>b>>ab;
        cout<<-(ab - a - b)<<endl;
    }
}
