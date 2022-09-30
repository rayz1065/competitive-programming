#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int campo[200][200];
    for(int i=0; i<200; i++)
        for(int j=0; j<200; j++)
            campo[i][j]=0;
    int N;
    in>>N;
    int semimax=0;
    for(int c=0; c<N; c++){
        int i1, i2, j1, j2;
        in>>i1>>j1>>i2>>j2;
        for(int i=i1; i<i2; i++){
            for(int j=j2; j<j1; j++){
                campo[i+100][j+100]++;
                if(campo[i+100][j+100]>semimax)
                    semimax=campo[i+100][j+100];
            }
        }
    }
    out<<semimax;
}
