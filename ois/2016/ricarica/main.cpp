#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, M;
    in>>N>>M;
    int C=0, Cmin=0;
    int A, B=0;
    for(int i=0; i<N; i++){
        in>>A;
        if(A>B+1){
            C=C-(A-B-1);
            Cmin=min(C, Cmin);
        }
        in>>B;
        C+=B-A+1;
    }
    C=C-(M-B);
    Cmin=min(C, Cmin);
    out<<abs(Cmin)+1;
}
