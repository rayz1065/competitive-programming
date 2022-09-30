#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
int togliX(int X, int Y, int Z, int W){
    X=max(0, X-W);
    Z+=max(0, Y-5000);
    if(Z>10000)
        return X*40+max(0, Z-10000)*60+10000*20;
    else
        return X*40+Z*20;
}

int togliY(int X, int Y, int Z, int W){
    Y=max(0, Y-W);
    Z+=max(0, Y-5000);
    if(Z>10000)
        return X*40+max(0, Z-10000)*60+10000*20;
    else
        return X*40+Z*20;
}

int togliZ(int X, int Y, int Z, int W){
    Z=max(0, Z-W);
    Z+=max(0, Y-5000);
    if(Z>10000)
        return X*40+max(0, Z-10000)*60+10000*20;
    else
        return X*40+Z*20;
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int X, Y, Z, W;
    in>>X>>Y>>Z>>W;
    cout<<min(min(togliZ(X, Y, Z, W),togliY(X, Y, Z, W)), togliX(X, Y, Z, W));
}
