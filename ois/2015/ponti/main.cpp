#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n, m;
    in>>n>>m;
    int costruire=n-1;
    vector<int> isole(n);
    vector<bool> albero(n);
    vector<vector<int> > sottoposti(n);
    for(int i=0; i<n; i++)
        isole[i]=i;
    for(int i=0; i<m; i++){
        int a,b;
        in>>a>>b;
        if(isole[b]!=isole[a]){
            costruire--;
            if(!albero[a]&&!albero[b]){
                albero[a]=true;
                albero[b]=true;
                isole[b]=a;
                sottoposti[a].push_back(b);
            }
            else if(!albero[b]){
                isole[b]=isole[a];
                albero[b]=true;
                sottoposti[isole[a]].push_back(b);
            }
            else if(!albero[a]){
                isole[a]=isole[b];
                albero[a]=true;
                sottoposti[isole[b]].push_back(a);
            }
            else{
                int origine=isole[b];
                for(int c=0; c<sottoposti[origine].size(); c++){
                    isole[sottoposti[origine][c]]=isole[a];
                    sottoposti[isole[a]].push_back(sottoposti[origine][c]);
                }
                sottoposti[origine].clear();
                isole[origine]=isole[a];
                sottoposti[isole[a]].push_back(origine);
            }
        }
    }
    out<<costruire;
}
