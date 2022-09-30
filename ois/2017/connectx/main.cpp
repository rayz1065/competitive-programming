#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int x, righe, colonne, cont(-1);
    in>>x>>righe>>colonne;
    if(colonne%2==0){
        for(int i=0; i<righe; i++){
            cont=(cont+1)%4;
            for(int j=0; cont<2&&j<colonne; j++)
                out<<j<<" ";
            for(int j=1; cont>=2&&j<colonne; j++)
                out<<j<<" ";
            if(cont>=2)
                out<<"0 ";
        }
    }
    else{
        for(int i=0; i<righe; i++){
            for(int j=0; j+3<colonne; j=j+4){
                out<<j<<" "<<j+2<<" "<<j+1<<" "<<j+3<<" ";
            }
            if(colonne%4==1)
                out<<colonne-1<<" ";
            else
                out<<colonne-3<<" "<<colonne-1<<" "<<colonne-2<<" ";
        }
    }
}
