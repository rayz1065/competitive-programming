#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N, K;
    in>>N>>K;
    set<int> insieme;
    for(int i=0; i<N; i++){
        int val;
        in>>val;
        insieme.insert(val);
    }

    int S=0;
    while(!insieme.empty()){
        S++;

        insieme.erase(*insieme.begin()*K);
        insieme.erase(insieme.begin());
    }
    out<<S;
}
