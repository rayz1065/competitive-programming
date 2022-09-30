#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    vector<double> dista;
    for(int i=0; i<N; i++){
        long x, y, z;
        in>>x>>y>>z;
        dista.push_back(sqrt(x*x+y*y+z*z));
    }
    sort(dista.begin(), dista.begin()+N);
    int Q;
    in>>Q;
    vector<double>::iterator limite;
    for(int i=0; i<Q; i++){
        long D;
        in>>D;
        limite=upper_bound(dista.begin(), dista.begin()+N, D);
        out<<limite-dista.begin()<<endl;
    }
}
