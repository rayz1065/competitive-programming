#include <iostream>
#include <fstream>

using namespace std;

int Coll[10001];

int collatz(int N){
    if(N==1)
        return 0;
    if(N<=10000&&Coll[N]==1000000){
        if(N%2==0)
            Coll[N]=collatz(N/2)+1;
        else
            Coll[N]=collatz(3*N+1)+1;
    }
    else if(N>10000){
        if(N%2==0)
            return collatz(N/2)+1;
        else
            return collatz(3*N+1);
    }
    return Coll[N];
}

int pcollatz(int N, int pass, int maxP){
    if(N==1)
        return pass;
    if(pass>maxP)
        return maxP+1;
    if(N%2==0)
        return pcollatz(N/2, pass+1, maxP);
    return pcollatz(5*N+1, pass+1, maxP);
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int A, B;
    in>>A>>B;
    int S=0;
    for(int i=0; i<10000; i++)
        Coll[i]=1000000;
    for(int c=A; c<=B; c++){
        int maxP=collatz(c);
        if(pcollatz(c, 0, maxP)<maxP)
            S++;
    }
    out<<S;
}
