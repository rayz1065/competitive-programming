#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, corr=0, ap=0, error=0, aperte[100];
    cin>>n;
    int parentesi[n];
    char lett;
    if(n%2==0){
        for(int cont=0; cont<n; cont++){
            cin>>lett;
            if(lett=='<')(parentesi[cont]=1);
            if(lett=='(')(parentesi[cont]=2);
            if(lett=='[')(parentesi[cont]=3);
            if(lett=='{')(parentesi[cont]=4);
            if(lett=='>')(parentesi[cont]=-1);
            if(lett==')')(parentesi[cont]=-2);
            if(lett==']')(parentesi[cont]=-3);
            if(lett=='}')(parentesi[cont]=-4);
        }
    }
    else(error=1);
    if(parentesi[0]<0)(error=1);
    else (aperte[0]=parentesi[0]);
    for(int cont=1; cont<n&&error==0; cont++){
        if(parentesi[cont]>0){
            ap++;
            aperte[ap]=parentesi[cont];
        }
        else{
            if(aperte[ap]+parentesi[cont]==0){
                aperte[ap]=0;
                ap--;
                corr=corr+2;
            }
        }
    }
    if(corr==n)(cout<<"corretta");
    else(cout<<"malformata");
}
