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
    int ela[N], salti[N+1];
    for(int i=0; i<N; i++){
        in>>ela[i];
        salti[i]=100005;
    }
    salti[0]=0;
    salti[N]=100005;
    for(int i=0; i<N; i++){
        int j=min(N, i+ela[i]);
        while(j>i&&salti[i]+1<salti[j]){
            salti[j]=salti[i]+1;
            j--;
        }
    }
    out<<salti[N];
}
