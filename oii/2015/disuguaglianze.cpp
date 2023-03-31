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
    int sol[N];
    char disug[N];
    for(int i=0; i<N; i++)
        sol[i]=i+1;
    for(int i=1; i<N; i++){
        in>>disug[i];
        int j=i;
        while(j>0&&((disug[j]=='>'&&sol[j-1]<sol[j])||(disug[j]=='<'&&sol[j-1]>sol[j]))){
            swap(sol[j], sol[j-1]);
            j--;
        }
    }
    for(int i=0; i<N; i++)
        out<<sol[i]<<" ";
}
