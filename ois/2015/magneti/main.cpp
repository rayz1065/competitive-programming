#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, totp=0, totm=0;
    char magnet;
    cin>>n;
    for(int cont=0;cont<n;cont++){
        cin>>magnet;
        cin>>magnet;
        if(magnet=='+')(totp++);
        if(magnet=='-')(totm++);
        cin>>magnet;
        cin>>magnet;
    }
    if(totp<totm){
        cout<<totp;
    }
    else{
        cout<<totm;
    }
}