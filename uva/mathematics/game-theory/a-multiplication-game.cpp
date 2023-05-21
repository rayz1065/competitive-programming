#include <bits/stdc++.h>
#define memoria 1000000
int memo[memoria];
using namespace std;

bool canWin(long long int a, unsigned int N){
    if(a<memoria){
        if(a*9>=N)
            return true;
        if(memo[a]==0)
            for(int i=2; i<=9&&a*9*i<N; i++)
                if(!canWin(a*i, N))
                    memo[a]=2;
        if(memo[a]==0)
            memo[a]=1;
        return memo[a]-1;
    }
    for(int i=2; i<=9&&a*9*i<N; i++)
        if(!canWin(a*i, N))
            return true;
    return false;
}

int main(){
    fstream in, out;
    out.open("output.txt", ios::out);
    unsigned int N;
    while(cin>>N){
        for(int i=0; i<N&&i<memoria; i++)
            memo[i]=0;
        cout<<(canWin(1, N)?"Stan wins.":"Ollie wins.")<<endl;
    }
}
