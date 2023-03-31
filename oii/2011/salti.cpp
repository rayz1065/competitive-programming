#include <bits/stdc++.h>

using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int T, c=0;
    in>>T;
    for(int i=0; ((unsigned int)1<<i)<=T; i++)
        if(T==(T|(1<<i)))
            c++;
    out<<c;
}
