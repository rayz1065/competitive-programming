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
    int dimF=N;
    string riga;
    string soluzione;
    getline(in, riga);
    getline(in, riga);
    int dime=riga.size();
    for(int i=0; i<N; i++){
        if(riga[i]=='&'){
            soluzione+=riga[i];
            while(i+4<dime&&riga[i+1]=='a'&&riga[i+2]=='m'&&riga[i+3]=='p'&&riga[i+4]==';'){
                i+=4;
                dimF-=4;
            }
        }
        else
            soluzione+=riga[i];
        if(i==riga.size()-1){
            N-=(riga.size()+1);
            getline(in, riga);
            i=-1;
            dime=riga.size();
            soluzione+='\n';
        }
    }
    out<<dimF<<endl;
    out<<soluzione;
}
