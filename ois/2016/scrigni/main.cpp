#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    double N;
    in>>N;
    out<<((N-1)*N)/4;
}
