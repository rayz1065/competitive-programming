#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int tessere[N][2];
    stack<vector<int> > check;
    for(int i=0; i<N; i++){
        int a,b;
        in>>a>>b;
        tessere[i][0]=a;
        tessere[i][1]=b;
    }
    vector<int> inserisci;
    for(int i=0; i<N; i++){
        for(int c=0; c<N; c++)
            if(c!=i)
                inserisci.push_back(c);
        inserisci.push_back(tessere[i][1]);
        check.push(inserisci);
        inserisci.back()=tessere[i][0];
        check.push(inserisci);
        inserisci.clear();
    }
    vector<int> ora;
    vector<int> temp;
    int cerca, dominomax=1;
    while(!check.empty()){
        ora=check.top();
        check.pop();
        for(int i=0; i<ora.size(); i++)
            cout<<ora[i]<<" ";
        cout<<endl;
        if((N-ora.size())+1>dominomax)
            if(ora.size()==1){
                out<<N;
                return 0;
            }
            else
                dominomax=(N-ora.size())+1;
        cerca=ora.back();
        for(int i=0; i<ora.size()-1; i++){
            if(tessere[ora[i]][0]==cerca){
                temp=ora;
                temp.erase(temp.begin()+i);
                temp.back()=tessere[ora[i]][1];
                check.push(temp);
            }
            else if(tessere[ora[i]][1]==cerca){
                temp=ora;
                temp.erase(temp.begin()+i);
                temp.back()=tessere[ora[i]][0];
                check.push(temp);
            }
        }
    }
    out<<dominomax;
}
