#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <fstream>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n;
    in>>n;
    vector <vector<int> > nodi(1002);
    bool mappa[1002][1002];
    for(int i=0; i<n; i++){
        int x, y;
        in>>x>>y;
        nodi[x].push_back(y);
        mappa[x][y]=true;
    }
    int x1(0), x2, y1, y2, lato(0);
    for(x1=0; x1<1000&&x1+lato<=1005; x1++){
        for(int i=0; nodi[x1].size()>1&&i<nodi[x1].size()-1; i++){
            y1=nodi[x1][i];
            for(int j=i+1; j<nodi[x1].size(); j++){
                y2=nodi[x1][j];
                x2=x1+abs(y2-y1);
                if(x2<1000&&mappa[x2][y1]&&mappa[x2][y2]&&abs(x2-x1)>lato)
                    lato=abs(x2-x1);
            }
        }
    }
    out<<lato;
}
