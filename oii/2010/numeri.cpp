#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, M;
    in>>M>>N;
    vector<long long> aiuola(N+1);
    aiuola[0]=0;
    in>>aiuola[1];
    if(aiuola[1]==0)
        aiuola.erase(aiuola.begin());
    for(int i=aiuola.size()-N+1; i<aiuola.size(); i++){
        in>>aiuola[i];
        aiuola[i]+=aiuola[i-1];
    }
    int S(0);
    for(int i=0; i<aiuola.size(); i++){
        if(binary_search(aiuola.begin()+i, aiuola.end(), aiuola[i]+M)){
            S+=upper_bound(aiuola.begin()+i, aiuola.end(), aiuola[i]+M)-lower_bound(aiuola.begin()+i, aiuola.end(), aiuola[i]+M);
        }
    }
    out<<S;
}
