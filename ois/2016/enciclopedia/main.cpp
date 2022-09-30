#include <iostream>
#include <fstream>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, K;
    in>>N>>K;
    string titoli[2*K];

    for(int i=0; i<2*K; i+=2){
        in>>titoli[i];
        for(int j=0; j<N/K-2; j++)
            in>>titoli[i+1];
        in>>titoli[i+1];
    }

    int len=0, oldLen=0;
    for(int i=0; i<K*2-1; i++){
        len=0;
        while(len<=titoli[i].size()&&len<=titoli[i+1].size()&&titoli[i][len]==titoli[i+1][len])
            len++;
        if(oldLen>len)
            for(int c=0; c<=oldLen&&c<titoli[i].size(); c++)
                out<<(char)(titoli[i][c]-32);
        else
            for(int c=0; c<=len&&c<titoli[i].size(); c++)
                out<<(char)(titoli[i][c]-32);
        oldLen=len;
        if(i%2==0)
            out<<'-';
        else
            out<<endl;
    }
    for(int c=0; c<=len&&c<titoli[K*2-1].size(); c++)
        out<<(char)(titoli[K*2-1][c]-32);
}
