#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    string canzone;
    in>>canzone;
    in>>canzone;
    bool fw=true;
    for(int i=0; i<canzone.size(); i++){
        if(i+2<canzone.size()&&canzone[i]=='P'&&canzone[i+1]=='a'&&canzone[i+2]=='H')
            i+=2;
        else if(i+3<canzone.size()&&canzone[i]=='T'&&canzone[i+1]=='u'&&canzone[i+2]=='N'&&canzone[i+3]=='Z')
            i+=3;
        else{
            if(!fw)
                out<<" ";
            while(i<canzone.size()&&!(i+2<canzone.size()&&canzone[i]=='P'&&canzone[i+1]=='a'&&canzone[i+2]=='H')&&!(i+3<canzone.size()&&canzone[i]=='T'&&canzone[i+1]=='u'&&canzone[i+2]=='N'&&canzone[i+3]=='Z')){
                out<<canzone[i];
                i++;
            }
            i--;
            fw=false;
        }
    }
}
