#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n, prezzo, paga=0, tot=0;
    cin>>n>>paga;
    for(int i=0; i<n; i++){
        tot+=paga;
        cin>>prezzo;
        paga++;
        if(prezzo<paga)
            paga=prezzo;
    }
    cout<<tot;
}
