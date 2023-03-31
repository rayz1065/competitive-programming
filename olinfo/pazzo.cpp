#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, M;
    in>>N>>M;
    int ipPos[N];
    int aula[N];
    for(int i=0; i<N; i++){
        aula[i]=i;
        ipPos[i]=i;
    }
    int a, b;
    for(int c=0; c<M; c++){
        in>>a>>b;
        swap(aula[ipPos[a]], aula[ipPos[b]]);
        swap(ipPos[a], ipPos[b]);
    }
    out<<aula[0];
}
