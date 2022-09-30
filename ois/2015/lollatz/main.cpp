#include <iostream>
#include <cstdio>
#include <fstream>

using namespace std;

int calcola(int N){
    while(N%10!=0){
        N*=(N%10-1);
        N/=2;
    }
    return N;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    out<<calcola(N);
}