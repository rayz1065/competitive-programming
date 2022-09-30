#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int T;
    in>>T;
    for(int val=0; val<T; val++){
        int N, S=0;
        in>>N;
        for(int i=0; 2*i*i<=N; i++)
            for(int j=i; i*i+2*j*j<=N; j++)
                for(int c=j; i*i+j*j+2*c*c<=N; c++){
                    int k=sqrt(N-(i*i+j*j+c*c));
                    if(i*i+j*j+c*c+k*k==N)
                        S++;
                }
        out<<S<<" ";
    }
}
