#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, P, freqmax(1), h(105000), pozmaxxDlel(105000);
    in>>N;
    unordered_map <int, int> altezze;
    altezze[h]=1;
    for(int i=0; i<N; i++){
        in>>P;
        h+=P;
        altezze[h]++;
        if(altezze[h]>freqmax){
            freqmax=altezze[h];
            pozmaxxDlel=h;
        }
    }
    out<<pozmaxxDlel-100000;
}
