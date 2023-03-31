#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
bool isPrime(int n){
    if(n%2==0)
        return false;
    for(int i=3; i<=sqrt(n); i=i+2){
        if(n%i==0)
            return false;
    }
    return true;
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    vector<int> primi;
    primi.push_back(2);
    for(int i=3; i<100010; i++)
        if(isPrime(i))
            primi.push_back(i);
    vector<int>::iterator it;
    int r, c;
    in>>r>>c;
    int righe[r]={0}, colonne[c]={0};
    for(int i=0; i<r; i++){
        int num;
        for(int j=0; j<c; j++){
            in>>num;
            if(!binary_search(primi.begin(), primi.end(), num)){
                it=upper_bound(primi.begin(), primi.end(), num);
                righe[i]+=*it-num;
                colonne[j]+=*it-num;
            }
        }
    }
    int primin=righe[0];
    for(int i=1; i<r; i++){
        primin=min(primin, righe[i]);
    }
    for(int i=0; i<c; i++){
        primin=min(primin, colonne[i]);
    }
    out<<primin;
}
