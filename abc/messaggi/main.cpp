#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, R;
    in>>N>>R;
    map<string, vector<string> > ricevuti;
    map<string, vector<string> > inviati;
    for(int i=0; i<N; i++){
         string mittente, destinatario;
         in>>mittente>>destinatario;
         ricevuti[destinatario].push_back(mittente);
         inviati[mittente].push_back(destinatario);
    }
    for(int i=0; i<N; i++){
        string pers, oper;
        in>>pers>>oper;
        if(oper=="INVIATI"){
            out<<inviati[pers].size()<<" ";
            for(int c=0; c<inviati[pers].size(); c++)
                out<<inviati[pers][c]<<" ";
            out<<endl;
        }
        if(oper=="RICEVUTI"){
            out<<ricevuti[pers].size()<<" ";
            for(int c=0; c<ricevuti[pers].size(); c++)
                out<<ricevuti[pers][c]<<" ";
            out<<endl;
        }
    }
}
