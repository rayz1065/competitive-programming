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
    int N, M, K;
    in>>N>>M>>K;
    vector<vector<int> > strade(N+1);
    for(int i=0; i<K; i++){
        int pos;
        in>>pos;
        nodi[pos].second=true;
    }
    for(int i=0; i<M; i++){
        int a, b;
        in>>a>>b;
        strade[a].push_back(b);
        strade[b].push_back(a);
    }

}
