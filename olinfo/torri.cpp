#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin>>n;
    int alte[n], costo[n], val[n], somma=0, mag=0;
    for(int i=0; i<n; i++){
        cin>>alte[i];
        cin>>costo[i];
        somma+=costo[i];
    }
    for(int i=n-1; i>=0; i--){
        val[i]=0;
        for(int j=i; j<n; j++){
            if(alte[i]>alte[j]&&val[j]>val[i]){
                val[i]=val[j];
            }
        }
        val[i]+=costo[i];
        if(val[i]>mag){
            mag=val[i];
        }
    }
    cout<<somma-mag;
}
