#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    vector<int> numeri(N);
    for(int i=0; i<N; i++)
        in>>numeri[i];
    sort(numeri.begin(), numeri.begin()+N);
    int posPari=1;
    while(numeri[posPari]%2!=0)
        posPari++;
    int parimin=numeri[posPari];
    numeri.erase(numeri.begin()+posPari);
    for(int i=1; i<numeri.size(); i++)
        out<<numeri[numeri.size()-i-1]<<" ";
    out<<parimin<<" "<<0;
}
