#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int H, N;
    in>>H>>N;
    char paint[N];
    for(int i=0; i<N; i++){
        int A, B;
        in>>A>>B;
        if(A<H&&B<H)
            paint[i]='L';
        else if(A>H&&B>H)
            paint[i]='R';
        else
            paint[i]='W';
    }
    int i=0, j=N-1;
    int S=0;
    while(i<j){
        while(paint[i]!='R'&&i<=j)
            i++;
        while(paint[j]!='L'&&i<=j)
            j--;
        if(i<j){
            S++;
            i++;
            j--;
        }
    }
    out<<S;
}
