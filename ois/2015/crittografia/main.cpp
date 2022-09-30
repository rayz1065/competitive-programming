#include <iostream>
#include <fstream>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int power10[11];
    power10[0]=1;
    for(int i=1; i<10; i++)
        power10[i]=power10[i-1]*10;

    int K=0;
    while(K<10&&power10[K]<=N)
        K++;
    int S=N;
    for(int i=0; i<K; i++){
        S+=power10[K-i-1]*(N%10);
        N/=10;
    }
    out<<S;
}
