#include <bits/stdc++.h>
#define MAXN 41
using namespace std;

bool isPrime[MAXN];
vector<int> primi;

void calcolaPrimi(){
    for(int i=2; i<MAXN; i++)
        isPrime[i] = true;

    for(int i=2; i<MAXN; i++)
        if(isPrime[i]){
            primi.push_back(i);
            for(int j=i*2; j<MAXN; j+=i)
                isPrime[j] = false;
        }
}

int main(){
    calcolaPrimi();
    int T;
    cin>>T;

    for(int i=0; i<T; i++){
        int N;
        cin>>N;
        int S=1;
        for(int c=0; c<primi.size(); c++){
            for(int pw=primi[c]; pw<=N; pw*=primi[c])
                if(S%pw!=0)
                    S*=primi[c];
        }
        cout<<S<<endl;
    }
}
