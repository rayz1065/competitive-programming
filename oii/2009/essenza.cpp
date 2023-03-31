#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k, j=0, maxi=0, maxj=0;
    cin>>k;
    cin>>n;
    int prezzi[n];
    for(int cont=0; cont<n;cont++){
        cin>>prezzi[cont];
    }
    for(int i=0; i<n; i++){
        j=i;
        for(; j<n&&j-i<=k; j++){
            if(prezzi[j]-prezzi[i]>prezzi[maxj]-prezzi[maxi]){
                maxj=j;
                maxi=i;
            }
        }
    }
    cout<<prezzi[maxj]-prezzi[maxi];
}
