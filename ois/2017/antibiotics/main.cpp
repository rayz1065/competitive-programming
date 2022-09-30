#include <iostream>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, T;
    in>>N>>T;
    unordered_map<int, int> oraLib;
    for(int i=0; i<N; i++){
        int ora;
        in>>ora;
        if(oraLib[ora%T]<ora+T)
            oraLib[ora%T]=ora+T;
    }
    int minimo=0;
    for(int i=0; i<T; i++)
        if(oraLib[i]<oraLib[minimo]){
            minimo=i;
            if(oraLib[minimo]==0){
                out<<minimo;
                return 0;
            }
        }
    out<<oraLib[minimo];
}
