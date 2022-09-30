#include <cstdio>
#include <iostream>
#include <queue>
#include <fstream>
#include <climits>

using namespace std;
std::queue<int> fontana;
std::vector<int> numeri(15000000,INT_MAX);

int pulisci(){
    int n, x;
    while(!fontana.empty()){
        x=1;
        n=fontana.front();
        if(n==0)
            return numeri[0];
        fontana.pop();
        if(n*2<15000000&&numeri[n*2]>numeri[n]+1){
            fontana.push(n*2);
            numeri[n*2]=numeri[n]+1;
        }
        if(numeri[n+1]>numeri[n]+1){
            fontana.push(n+1);
            numeri[n+1]=numeri[n]+1;
        }
        if(numeri[n-1]>numeri[n]+1){
            fontana.push(n-1);
            numeri[n-1]=numeri[n]+1;
        }
        while((n/x)%3==0){
            if(numeri[(n/x)/3]>numeri[n]+1){
                fontana.push(n/(x*3));
                numeri[(n/x)/3]=numeri[n]+1;
            }
            x*=3;
        }
    }
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int n;
    in>>n;
    fontana.push(n);
    numeri[n]=0;
    cout<<pulisci();

}
