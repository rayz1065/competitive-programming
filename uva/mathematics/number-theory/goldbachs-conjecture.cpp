#include <bits/stdc++.h>
#define MAXN 1000000
using namespace std;

bool isPrime[MAXN];
vector<int> primi;

int main(){
    primi.push_back(2);
    for(int i=3; i<MAXN; i+=2)
        isPrime[i]=true;
    for(int i=3; i<MAXN; i+=2)
        if(isPrime[i]){
            primi.push_back(i);
            for(int j=2*i; j<MAXN; j+=i)
                isPrime[j]=false;
        }
    int N;
    cin>>N;
    while(N!=0){
        bool found=false;
        for(int i=0; N-primi[i]>=primi[i]&&!found; i++){
            if(isPrime[N-primi[i]]){
                cout<<N<<" = "<<primi[i]<<" + "<<N-primi[i]<<endl;
                found=true;
            }
        }
        cin>>N;
        //"Goldbach's conjecture is wrong." :P
    }
}
