#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n;
    string check, parola;
    in>>check>>n;
    int wps(1), owps(1), t(0);
    for(int i=0; i<n; t++){
        for(int c=0; c<owps; c++, i++){
            in>>parola;
            if(parola==check)
                wps++;
        }
        owps=wps;
    }
    cout<<t;
}
