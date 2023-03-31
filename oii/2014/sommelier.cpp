#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n, cont=0, maxv=0;
    cin>>n;
    int grado[n], val[n];
    for(int i=0; i<n; i++){
        cin>>grado[i];
    }
    for(int i=n-1; i>=0; i--){
        val[i]=1;
        cont=i+2;
        while(cont<n){
            if(grado[i]<=grado[cont]&&val[i]<val[cont]){
                val[i]=val[cont];
            }
            cont++;
        }
        val[i]++;
        if(val[i]>maxv){
            maxv=val[i];
        }
    }
    cout<<maxv;
}
