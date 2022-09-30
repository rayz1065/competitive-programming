#include <iostream>
#include <fstream>
#include <cstdio>
#include <unordered_map>

using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    int modaReq=0, S=0;
    unordered_map<int, int> played;
    unordered_map<int, bool> wasModa;
    for(int i=0; i<N; i++){
        int canzone;
        in>>canzone;
        played[canzone]++;
        if(played[canzone]>=modaReq){
            modaReq=played[canzone];
           if(!wasModa[canzone]){
                wasModa[canzone]=true;
                S++;
           }
        }
    }
    out<<S;
}
