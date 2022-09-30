#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, a=0, numInv=0, cif=0;
    bool error=0;
    cin>>n;
    a=n;
    while(a!=0&&error==0){
        cif=a%10;
        if(cif==3||cif==4||cif==7)
            error=1;
        else if(cif==0){
            if(numInv==0){
                error=1;
            }
            numInv=numInv*10;
        }
        else if(cif==1)
            numInv=numInv*10+1;
        else if(cif==2)
            numInv=numInv*10+2;
        else if(cif==5)
            numInv=numInv*10+5;
        else if(cif==6)
            numInv=numInv*10+9;
        else if(cif==8)
            numInv=numInv*10+8;
        else
            numInv=numInv*10+6;
        a=(a-cif)/10;
    }
    if(error==1)
        cout<<n;
    else if(numInv<n)
        cout<<numInv;
    else
        cout<<n;
}