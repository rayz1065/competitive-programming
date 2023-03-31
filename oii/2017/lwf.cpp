#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define MAX 30

void Fibonacci(int fibo[]){
    fibo[0]=1;
    fibo[1]=1;
    for(int i=2; i<MAX; i++)
        fibo[i]=fibo[i-1]+fibo[i-2];
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int fibo[MAX];
    Fibonacci(fibo);
    int N;
    in>>N;
    bool preso[MAX];
    fill(preso, preso+MAX, false);
    int posM=0;
    for(int i=MAX-1; i>=0; i--){
        if(fibo[i]<=N){
            N-=fibo[i];
            preso[i]=true;
            if(i>posM)
                posM=i;
        }
    }
    for(int i=0; i<=posM; i++)
        out<<preso[i];
}
