#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int D, N;
    in>>D>>N;
    int giorni[D]={0};
    for(int i=0; i<N; i++){
        int giorno;
        in>>giorno;
        giorni[giorno-1]++;
    }
    for(int g=0; g<7; g++){
        for(int c=0; c*7+g<D; c++){
            if(giorni[c*7+g]<10)
                out<<'.';
            else if(giorni[c*7+g]<20)
                out<<'o';
            else
                out<<'O';
        }
        out<<endl;
    }
}
