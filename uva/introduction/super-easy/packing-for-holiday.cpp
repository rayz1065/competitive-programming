#include <iostream>
#define dim 20
using namespace std;

int main(){
    int T;
    cin>>T;
    for(int i=0; i<T; i++){
        int L, W, H;
        cin>>L>>W>>H;
        if(L>dim||W>dim||H>dim)
            cout<<"Case "<<i+1<<": bad\n";
        else
            cout<<"Case "<<i+1<<": good\n";
    }
}
