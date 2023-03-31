#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N, cont=1;
    cin>>N;
    while(N!=1){
        if(N%2==0)
            N=N/2;
        else
            N=N*3+1;
        cont++;
    }
    cout<<cont;
}
