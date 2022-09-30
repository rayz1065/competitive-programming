#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>


using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n, k;
    in>>n>>k;
    int altezze[n];
    for(int i=0; i<n; i++)
        in>>altezze[i];
    sort(altezze,altezze+n);
    int minimo=altezze[n-1];
    for(int i=0; i<n-k+1; i++){
        if(altezze[i+k-1]-altezze[i]<minimo)
            minimo=altezze[i+k-1]-altezze[i];
    }
    out<<minimo;
}
