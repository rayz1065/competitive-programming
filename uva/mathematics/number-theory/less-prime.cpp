#include <bits/stdc++.h>
#define MAXN 11000
using namespace std;

bool isPrime[MAXN];
vector<int> primi;

int main(){
    primi.push_back(2);
    isPrime[2]=true;
    for(int i=3; i<MAXN; i+=2)
        isPrime[i]=true;
    for(int i=3; i<MAXN; i+=2)
        if(isPrime[i]){
            primi.push_back(i);
            for(int j=i*2; j<MAXN; j+=i)
                isPrime[j]=false;
        }

    int M;
    cin>>M;
    for(int c=0; c<M; c++){
        int N;
        cin>>N;
        int npx=0, x=0, p=0;
        for(int i=0; primi[i]<N; i++){
            if(N-(N/primi[i])*primi[i]>npx){
                npx=N-(N/primi[i])*primi[i];
                x=primi[i];
                p=N/primi[i];
            }
        }
        cout<<x<<endl;
        //n-p*x massimizzare
        //p*x<=n<(p+1)*x
    }
}
