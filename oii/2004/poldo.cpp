#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n, cont=0, maxv=0;
    cin>>n;
    int peso[n], val[n];
    for(int i=0; i<n; i++){
        cin>>peso[i];
    }
    for(int i=n-1; i>=0; i--){
        val[i]=0;
        cont=i;
        while(cont<n){
            if(peso[cont]<peso[i]&&val[i]<val[cont]){
                val[i]=val[cont];
            }
            cont++;
        }
        val[i]++;
        if(maxv<val[i]){
            maxv=val[i];
        }
    }
    cout<<maxv;
}
