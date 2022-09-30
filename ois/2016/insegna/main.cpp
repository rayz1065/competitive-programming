#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, sol=0, corr;
    cin>>n;
    char g[n-1], w[n-1];
    for(int cont=0;cont<n;cont++){
        cin>>g[cont];
    }
    for(int cont=0;cont<n;cont++){
        cin>>w[cont];
    }
    for(int cont=0;cont<n&&sol==0;cont++){
        for(int i=0;i<n;i++){
            if(g[i]==w[i+cont]||g[i]==w[i+cont-n]){
                corr=corr+1;
            }
            if(corr==n){
                sol=1;
            }
        }
    corr=0;
    }
    cout<<sol;
}
