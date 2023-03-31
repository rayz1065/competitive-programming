#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>
using namespace std;

#define modulo 1000000007

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    long long int N;
    long long int K;
    in>>N>>K;
    unordered_map<long long int, int> freq;
    for(int i=0; i<N; i++){
        long long int k;
        in>>k;
        freq[k]++;
    }
    long long int a=sqrt(K), S=0;
    if(a*a==K)
        S=((freq[a]*(freq[a]-1))/2)%modulo;
    for(int i=1; i<sqrt(K); i++)
        if(K%i==0)
            S=(S+(freq[i]*freq[K/i]))%modulo;
    out<<S;
}
