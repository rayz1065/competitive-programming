#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    string disord;
    in>>disord;
    long long S=0;
    int hellos=0;
    for(int i=0; i<disord.size()-4; i++){
        if(disord[i]=='h'){
            if(disord[i+1]=='e'&&disord[i+2]=='l'&&disord[i+3]=='l'&&disord[i+4]=='o'){
                hellos++;
                i+=4;
            }
        }
        else if(disord[i]=='w')
            if(disord[i+1]=='o'&&disord[i+2]=='r'&&disord[i+3]=='l'&&disord[i+4]=='d'){
                S+=hellos;
                i+=4;
            }
    }
    out<<S;
}
