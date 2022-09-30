#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>

using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    int sequ[N];
    int vale[N];
    for(int i=0; i<N; i++)
        in>>sequ[i];
    for(int i=N-1; i>=0; i--){
        vale[i]=0;
        for(int j=i+1; j<N; j++){
            if(vale[j]+1>vale[i]&&(sequ[j]<sequ[i]||sequ[j]%sequ[i]==0))
                vale[i]=vale[j]+1;
        }
    }
    out<<N-*max_element(vale, vale+N)-1;
}
