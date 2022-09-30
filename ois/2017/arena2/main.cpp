#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, E;
    in>>N>>E;
    int squadre[N]={0};
    int stolenF[N];
    for(int i=0; i<E; i++){
        int X, Y;
        in>>X>>Y;
        if(X!=Y){
            squadre[X]++;
            stolenF[Y]=X;
        }
        else
            squadre[stolenF[X]]--;
    }
    for(int i=0; i<N; i++)
        out<<squadre[i]<<" ";
}
