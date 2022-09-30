#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    vector<int> bravura(N);
    vector<vector<int> > albero(N);
    for(int i=0; i<N; i++){
        in>>bravura[i];
        int capo;
        in>>capo;
        if(capo!=-1)
            albero[capo].push_back(i);
    }
    queue<int> FF;
    int licenziati(0), pers;
    FF.push(0);
    while(!FF.empty()){
        pers=FF.front();
        FF.pop();
        for(int i=0; i<albero[pers].size(); i++){
            if(bravura[albero[pers][i]]>bravura[pers]){
                licenziati++;
                bravura[albero[pers][i]]=bravura[pers];
            }
            FF.push(albero[pers][i]);
        }
    }
    out<<licenziati;
}
