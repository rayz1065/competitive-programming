#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    string primo;
    string ultimo;
    in>>primo;
    ultimo=primo;
    for(int i=0; i<N-1; i++){
        string numero;
        in>>numero;
        if(numero<primo)
            primo=numero;
        if(numero>ultimo)
            ultimo=numero;
    }
    int S=0;
    while(S<primo.size()&&primo[S]==ultimo[S])
        S++;
    out<<S;
}
