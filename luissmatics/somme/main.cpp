#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    set<pair<int, int> > numeri;
    for(int i=0; i<N; i++){
        int a;
        in>>a;
        numeri.insert({a, i});
    }
    int cont=N, S=0;
    while(numeri.size()!=1){
        int a=numeri.begin()->first;
        numeri.erase(numeri.begin());
        a+=numeri.begin()->first;
        numeri.erase(numeri.begin());
        S+=a;
        numeri.insert({a, cont});
        cont++;
    }
    out<<S;
}
