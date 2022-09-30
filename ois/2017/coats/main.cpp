#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, tot(0), due[]={0,0,0};
    in>>N;
    for(int i=0; i<N; i++){
        int coats;
        in>>coats;
        tot+=coats;
        due[coats]++;
    }
    cout<<float(due[2])*(float(due[2]+1)/2)/tot;
}
