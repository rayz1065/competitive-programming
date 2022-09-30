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
    bool rimasto[N];
    for(int i=0; i<N; i++)
        in>>rimasto[i];
    int S=0;
    for(int i=0; i<M; i++){
        int da, a;
        in>>da>>a;
        if(rimasto[da]&&rimasto[a])
            S++;
    }
    out<<S;
}
