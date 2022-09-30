#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n, q;
    in>>n>>q;
    set<vector<int> > prodotti;
    vector<int> a(q);
    for(int i=0; i<n; i++){
        for(int j=0; j<q; j++)
            in>>a[j];
        prodotti.insert(a);
    }
    vector<int> b(q);
    a=*prodotti.begin();
    prodotti.erase(prodotti.begin());
    int somiglianti(0);
    for(int i=0; i<n-1; i++){
        b=*prodotti.begin();
        prodotti.erase(prodotti.begin());
        for(int c=0; c<q&&a[c]==b[c]; c++){
            if(c+1>somiglianti)
                somiglianti=c+1;
        }
        a=b;
    }
    out<<somiglianti;
}
