#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    string a, b;
    in>>b;
    in>>a;
    int sott[b.size()];
    for(int i=0; i<b.size(); i++)
        sott[i]=0;
    for(int i=0; i<a.size(); i++){
        for(int c=b.size()-1; c>=0; c--){
            if(a[i]==b[c])
                if(c==0)
                    sott[0]++;
                else
                    sott[c]=(sott[c]+sott[c-1])%1000000007;
        }
    }
    out<<sott[b.size()-1];
}