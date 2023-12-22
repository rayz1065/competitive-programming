#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

bool isPrime[MAXN];
vector<int> primi;

void calcolaPrimi(){
    for(int i=3; i<MAXN; i+=2)
        isPrime[i] = true;

    primi.push_back(2);
    for(int i=3; i<MAXN; i+=2)
        if(isPrime[i]){
            primi.push_back(i);
            for(int j=2*i; j<MAXN; j+=i)
                isPrime[j] = false;
        }
}

int main(){
    calcolaPrimi();
    int T;
    cin>>T;
    for(int i=0; i<T; i++){
        long long N;
        cin>>N;
        for(int c=0; primi[c]<=sqrt(N); c++){
            while(N%primi[c]==0&&N>primi[c])
                N/=primi[c];
        }
        cout<<N<<endl;
    }
}
