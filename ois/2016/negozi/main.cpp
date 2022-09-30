#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, Q;
    in>>N>>Q;
    vector<vector<int> > negozi(100000);
    for(int i=0; i<N; i++){
        int tipo;
        in>>tipo;
        negozi[tipo].push_back(i);
    }
    vector<int>::iterator up;
    for(int i=0; i<Q; i++){
        int a, b;
        in>>a>>b;
        up=upper_bound(negozi[b].begin(), negozi[b].end(), a);
        if(up==negozi[b].begin())
            out<<abs(*up-a)<<endl;
        else{
            int mag=abs(*up-a);
            up--;
            out<<min(mag, abs(*up-a))<<endl;
        }
    }
}
