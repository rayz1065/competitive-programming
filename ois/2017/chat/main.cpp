#include <cstdio>
#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_set>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n;
    in>>n;
    unordered_set<string> usati;
    stack<string> user;
    for(int i=0; i<n; i++){
        string nick;
        in>>nick;
        user.push(nick);
    }
    int osize;
    for(int i=n-1; i>=0; i--){
        osize=usati.size();
        usati.insert(user.top());
        if(usati.size()!=osize)
            out<<user.top()<<endl;
        user.pop();
    }
}
