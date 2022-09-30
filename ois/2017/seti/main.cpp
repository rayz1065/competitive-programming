#include <iostream>
#include <iostream>
#include <fstream>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int antenne[N];
    int interf;
    in>>interf;
    antenne[0]=2;
    for(int i=1; i<N; i++){
        in>>interf;
        if(i-interf-1<0)
            antenne[i]=antenne[i-1]+1;
        else{
            antenne[i]=antenne[i-1]+antenne[i-interf-1];
            if(antenne[i]>1000000007)
                antenne[i]=antenne[i]%1000000007;
        }
    }
    out<<antenne[N-1];
}
