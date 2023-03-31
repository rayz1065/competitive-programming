#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N, M, pos, dest;
    in>>N>>M>>pos>>dest;
    int lum[50001], dire[50001];
    bool visited[50001];
    for(int i=0; i<M; i++){
        int a, b, l;
        in>>a>>b>>l;
        if(l<lum[a]||lum[a]==0){
            lum[a]=l;
            dire[a]=b;
        }
        if(l<lum[b]||lum[b]==0){
            lum[b]=l;
            dire[b]=a;
        }
    }
    int pas=0;
    while(!visited[pos]&&pos!=dest){
        visited[pos]=true;
        pos=dire[pos];
        pas++;
    }
    if(pos==dest)
        out<<pas;
    else
        out<<-1;
}
