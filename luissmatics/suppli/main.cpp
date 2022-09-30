#include <iostream>
#include <fstream>
#include <vector>
#define MAXN 1000
using namespace std;

bool found[MAXN];
vector<int> iniziali;

void expand(int nodo){
    for(auto i:iniziali){
        if(i + nodo < MAXN && !found[i + nodo]){
            found[i + nodo] = true;
            expand(i + nodo);
        }
    }
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    for(int i = 0; i < N; i++){
        int m;
        in>>m;
        found[m] = true;
        iniziali.push_back(m);
    }

    for(auto i:iniziali)
        expand(i);

    //for(int i = 0; i < MAXN; i++)
    //    cout<<((found[i])?"o":"-");

    for(int i = MAXN - 1; i >= 0; i--)
        if(!found[i]){
            out<<i;
            return 0;
        }
}
