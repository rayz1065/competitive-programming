#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n, b;
    in>>n>>b;
    int menu[n];
    for(int i=0; i<n; i++)
        in>>menu[i];
    int scelta[n][b+1];
    sort(menu, menu+n);
    for(int j=0; j<=b; j++)
        if(menu[0]<=j)
            scelta[0][j]=menu[0];
        else
            scelta[0][j]=0;
    for(int i=1; i<n; i++){
        for(int j=0; j<=b; j++){
            if(menu[i]<=j&&menu[i]+scelta[i-1][j-menu[i]]>scelta[i-1][j])
                scelta[i][j]=menu[i]+scelta[i-1][j-menu[i]];
            else
                scelta[i][j]=scelta[i-1][j];
        }
    }
    for(int i=n-1, j=scelta[n-1][b]; i>=0; i--){
        if(i==0){
            if(j>0)
                out<<menu[0];
        }
        else if(scelta[i][j]!=scelta[i-1][j]){
            out<<menu[i]<<endl;
            j-=menu[i];
        }
    }
}
