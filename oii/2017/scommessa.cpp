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
    int carta, pari=0;
    vector<int> rimangono;
    for(int i=0; i<N; i++){
        in>>carta;
        if(carta%2==0){
            if(pari*2==i)
                rimangono.push_back(carta);
            pari++;
        }
    }
    out<<rimangono.size()<<endl;
    for(int i=0; i<rimangono.size(); i++)
        out<<rimangono[i]<<" ";
}
