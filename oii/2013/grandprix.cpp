#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, M;
    in>>N>>M;
    int gara[N];
    int pos[N];
    for(int i=0; i<N; i++){
        int macchina;
        in>>macchina;
        macchina--;
        gara[i]=macchina;
        pos[macchina]=i;
    }
    for(int i=0; i<M; i++){
        int a, b;
        in>>a>>b;
        a--;
        b--;
        swap(gara[pos[a]], gara[pos[b]]);
        swap(pos[a], pos[b]);
    }
    out<<gara[0]+1;
}
