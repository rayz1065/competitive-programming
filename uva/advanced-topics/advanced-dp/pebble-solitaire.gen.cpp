#include <bits/stdc++.h>
#define MAXDIM 12
using namespace std;

int main(){
    fstream in, out;
    out.open("input.txt", ios::out);
    short disp=0;
    while(disp<4096){
        for(int i=0; i<MAXDIM; i++)
            out<<((disp==(disp|(1<<i)))?'o':'-');
        out<<endl;
        disp++;
    }
}
