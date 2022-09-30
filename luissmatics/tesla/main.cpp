#include <iostream>
#include <fstream>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int S=0, benzina[N];
    for(int i=0; i<N; i++){
        in>>benzina[i];
        benzina[i]-=10;
    }

    for(int i=0; i<N; i++){
        S=0;
        int j;
        for(j=i; j<N&&S>=0; j++)
            S+=benzina[j];
        if(j==N)
            for(j=0; j<i&&S>=0; j++)
                S+=benzina[j];
        if(S==0){
            out<<i+1;
            return 0;
        }
    }
}
