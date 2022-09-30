#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n,m;
    in>>n>>m;
    int altezze[n];
    vector<vector<int> > grafo(n);
    vector<bool> passato(n,0);
    for(int i=0; i<n; i++)
        in>>altezze[i];
    for(int i=0; i<m; i++){
        int a,b;
        in>>a>>b;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    bool arrivato=false;
    int parte=0, arrivada;
    passato[0]=true;
    while(!arrivato){
        int arrivo=grafo[parte][0];
        for(int c=0; c<grafo[parte].size(); c++)
            if(arrivo==arrivada||altezze[grafo[parte][c]]<altezze[arrivo]&&grafo[parte][c]!=arrivada)
                arrivo=grafo[parte][c];
        if(passato[arrivo]==true||(grafo[parte].size()==1&&parte!=0)){
            arrivato=true;
            if(grafo[parte].size()>1)
                parte=arrivo;
        }
        else{
            passato[arrivo]=1;
            arrivada=parte;
            parte=arrivo;
        }
    }
    out<<parte;
}
