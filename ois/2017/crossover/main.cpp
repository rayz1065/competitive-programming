#include <cstdio>
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    string sa,sb;
    in>>sa>>sb;
    vector<char> a;
    vector<char> b;
    for(int i=0; i<sa.size(); i++)
        a.push_back(sa[i]);
    for(int i=0; i<sb.size(); i++)
        b.push_back(sb[i]);
    stack<char> ultimi;
    bool inizio=true;
    while(a.size()>0&&b.size()>0){
        if(inizio){
            if(a[0]==b[b.size()-1])
                inizio=!inizio;
            else{
                out<<b[b.size()-1];
                ultimi.push(a[0]);
            }
            a.erase(a.begin());
            b.erase(b.begin()+b.size()-1);
        }
        else{
            if(b[0]==a[a.size()-1])
                inizio=!inizio;
            else{
                out<<a[a.size()-1];
                ultimi.push(b[0]);
            }
            b.erase(b.begin());
            a.erase(a.begin()+a.size()-1);
        }
    }
    for(int i=0; i<a.size(); i++)
        out<<a[i];
    for(int i=0; i<b.size(); i++)
        out<<b[i];
    while(!ultimi.empty()){
        out<<ultimi.top();
        ultimi.pop();
    }
}