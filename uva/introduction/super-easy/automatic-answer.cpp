#include <iostream>
#include <fstream>
using namespace std;

int main(){
    fstream in, out;
    out.open("output.txt", ios::out);
    int K;
    cin>>K;
    while(K!=0){
        int N, M;
        cin>>N>>M;
        for(int i=0; i<K; i++){
            int X, Y;
            cin>>X>>Y;
            if(X>N&&Y>N)
                out<<"NE";
            else if(X>N&&Y<M)
                out<<"SE";
            else if(X<N&&Y>M)
                out<<"NO";
            else if(X<N&&Y<M)
                out<<"SO";
            else
                out<<"divisa";
            out<<endl;
        }
        cin>>K;
    }
}
