#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int foglio[N];
    for(int i=0; i<N; i++)
        in>>foglio[i];
    sort(foglio, foglio+N);

    long long S=0;
    for(int i=0; i<N-2&&foglio[i]+foglio[i+1]<foglio[N-1]; i++){
        int upper=i+2;
        for(int j=i+1; j<N-1&&foglio[i]+foglio[j]<foglio[N-1]; j++){
            upper=(upper_bound(foglio+upper, foglio+N, foglio[i]+foglio[j])-foglio);
            S+=N-upper;
        }
    }
    out<<S;
}
