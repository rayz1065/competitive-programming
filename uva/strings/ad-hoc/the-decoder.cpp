#include <bits/stdc++.h>

using namespace std;

int main(){
    string a;
    while(cin>>a){
        for(int i=0; i<a.size(); i++)
            cout<<(char)(a[i]-7);
        cout<<endl;
    }
}
