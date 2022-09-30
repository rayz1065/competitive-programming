#include <cstdio>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n;
    in>>n;
    int salvati(0);
    stack<int> pesci;
    for(int i=0; i<n; i++){
        int dire, peso;
        in>>dire>>peso;
        if(pesci.empty()){
            if(dire==1)
                salvati++;
            else
                pesci.push(peso);
        }
        else{
            if(dire==0)
                pesci.push(peso);
            else{
                bool dead=false;
                while(!dead)
                if(peso>pesci.top()){
                    pesci.pop();
                    if(pesci.empty()){
                        salvati++;
                        dead=true;
                    }
                }
                else
                    dead=true;
            }
        }
    }
    salvati+=pesci.size();
    out<<salvati;
}
