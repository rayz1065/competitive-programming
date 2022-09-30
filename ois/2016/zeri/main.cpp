#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    string striscia;
    getline(in, striscia);
    int num(0), x5(0), x2(0);
    for(int i=0; i<striscia.size()+1; i++){
        if(striscia[i]!='x'&&i!=striscia.size()){
            num=striscia[i]-48+num*10;
        }
        else{
            while(num%2==0){
                x2++;
                num/=2;
            }
            while(num%5==0){
                x5++;
                num/=5;
            }
            num=0;
        }
    }
    if(x2<x5)
        out<<x2;
    else
        out<<x5;
}
