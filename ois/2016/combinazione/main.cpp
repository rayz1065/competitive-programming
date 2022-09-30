#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    long n;
    cin>>n;
    vector<pair<long,long> > numeri(n);
    for(int i=0; i<n; i++){
        cin>>numeri[i].first;
        numeri[i].second=i;
    }
    sort(numeri.begin(), numeri.end());
    int tot=numeri[n-1].second;
    for(int i=n-2; i>=0; i--){
        tot+=abs(numeri[i].second-numeri[i+1].second);
    }
    cout<<tot;
}
