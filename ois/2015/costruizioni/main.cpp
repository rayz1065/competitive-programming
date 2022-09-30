#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n,k, somma(0);
    in>>n>>k;
    queue<int> fila;
    for(int i=0; i<k; i++){
        int edificio;
        in>>edificio;
        somma+=edificio;
        fila.push(edificio);
    }
    int minimo=somma;
    for(int i=k; i<n; i++){
        int edificio;
        in>>edificio;
        somma=somma-fila.front()+edificio;
        fila.pop();
        fila.push(edificio);
        if(somma<minimo)
            minimo=somma;
    }
    cout<<minimo;
}
