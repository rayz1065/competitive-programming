#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int div=1, S=1;
    while(N!=1){
        div++;
        while(N%div==0){
            N/=div;
            S++;
        }
    }
    out<<S;
}
