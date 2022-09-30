#include <cstdio>
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    string frase;
    getline(in, frase);
    stack<string> ordine;
    string parola;
    for(int i=0; i<frase.size(); i++){
        if(frase[i]==' '){
            ordine.push(parola);
            parola.clear();}
        else
            parola+=frase[i];
    }
    if(ordine.empty())
        cout<<parola;
    else
        cout<<parola<<" ";
    while(ordine.size()>1){
        cout<<ordine.top()<<" ";
        ordine.pop();}
    if(!ordine.empty())
        cout<<ordine.top();
}
