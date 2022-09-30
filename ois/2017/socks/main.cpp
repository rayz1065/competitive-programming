#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, C;
    long long S(0);
    in>>N>>C;
    set<int> scelti;
    vector<int> filo;
    int calzino, osize;
    for(int c=0; c<N; c++){
        in>>calzino;
        osize=scelti.size();
        scelti.insert(calzino);
        if(scelti.size()==osize){
            bool found=false;
            for(int i=0; i<filo.size()&&!found; i++)
                if(calzino==filo[i]){
                    found=true;
                    S+=i;
                }
        }
        else{
            filo.push_back(calzino);
            S+=filo.size()-1;
        }
    }
    cout<<S;
}
