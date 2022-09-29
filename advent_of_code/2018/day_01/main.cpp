#include <bits/stdc++.h>

using namespace std;

int main(){
    fstream in, out;
    in.open("input1.txt", ios::in);
    out.open("output1.txt", ios::out);

    int f = 0, a;
    while(in >> a){
        f+= a;
    }
    out<<f<<endl;
    cout<<f<<endl;
}
