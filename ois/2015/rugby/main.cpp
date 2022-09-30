#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int> > albero;
vector<int> bravura;

int DFS(int nodo){
    int bravuraDip=0;
    for(int i=0; i<albero[nodo].size(); i++)
        bravuraDip+=DFS(albero[nodo][i]);
    return max(bravura[nodo], bravuraDip);
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    bravura.resize(N);
    albero.resize(N);
    in>>bravura[0];
    int capo;
    in>>capo;
    for(int i=1; i<N; i++){
        in>>bravura[i]>>capo;
        albero[capo].push_back(i);
    }
    out<<DFS(0);
}
