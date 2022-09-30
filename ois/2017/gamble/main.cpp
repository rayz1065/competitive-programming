#include <cstdio>
#include <iostream>
#include <set>
#include <fstream>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n, k;
    in>>n>>k;
    long long somma(0);
    int num;
    if(n==k){
        for(int i=0; i<n; i++){
            in>>num;
            somma+=num;
            out<<somma<<" ";
        }
        return 0;
    }
    set<pair<int,int> > mano;
    for(int i=0; i<k; i++){
        in>>num;
        mano.insert({num,i});
        somma+=num;
        out<<somma<<" ";
    }
    for(int i=k; i<n; i++){
        in>>num;
        if(num>mano.begin()->first){
            somma=somma-mano.begin()->first+num;
            mano.erase(mano.begin());
            mano.insert({num,i});
        }
        out<<somma<<" ";
    }
}
