#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, bal=0, a, stangate=0;
    cin>>n;
    vector<int> nega;
    for(int cont=0;cont<n;cont++){
        cin>>a;
        if(a<0){
            nega.push_back(a);
        }
        bal=bal+a;
    }
    sort(nega.begin(),nega.end());
    while(bal<=0){
        bal=bal-2*nega[stangate];
        stangate++;
    }
    cout<<stangate;
}
