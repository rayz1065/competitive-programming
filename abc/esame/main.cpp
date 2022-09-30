#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int D[N];
    for(int i=0; i<N; i++)
        in>>D[i];

    int A[N]={}, B[N]={}; //A corrsiponde ad il primo che non interroga, B corrisponde all'ultimo che non interroga
    A[1]=D[1];
    A[2]=D[2];
    B[0]=D[0];
    B[1]=D[1];
    B[2]=D[2]+D[0];

    for(int i=3; i<N; i++)
        A[i]=D[i]+max(A[i-2], A[i-3]);

    for(int i=3; i<N-1; i++)
        B[i]=D[i]+max(B[i-2], B[i-3]);

    out<<max(*max_element(A+N-2, A+N), *max_element(B+N-3, B+N-1));
}
