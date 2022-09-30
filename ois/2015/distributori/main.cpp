#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int viaggio=0, n=0, maxkm=0,rif=0, fatti=0;
    cin>>n;
    cin>>maxkm;
    cin>>viaggio;
    int dist[n];
    for(int cont=0;cont<(n+1);cont++){
        cin>>dist[cont];
        if(cont==n){
            dist[cont]=viaggio;
        }
    }
    for(int cont=0;cont<(n+1);cont++){
        if((dist[cont]-fatti)==maxkm&&n!=cont){
            rif++;
            fatti=dist[cont];
        }
        else if((dist[cont]-fatti)>maxkm){
            rif++;
            fatti=dist[cont-1];
            if((dist[cont]-fatti)==maxkm){
                rif++;
                fatti=dist[cont];
            }
        }
    }
    cout<<rif;
}
