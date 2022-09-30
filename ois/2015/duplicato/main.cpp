#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    int N;
    in>>N;
    unordered_set<int> fogli;
    for(int i=0; i<2*N-1; i++){
        int pag;
        in>>pag;
        if(fogli.find(pag)!=fogli.end())
            fogli.erase(pag);
        else
            fogli.insert(pag);
    }
    out<<*fogli.begin();
}
