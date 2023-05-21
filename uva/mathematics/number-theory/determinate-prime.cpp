#include <bits/stdc++.h>
#define MAXN 40000
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

    int A, B;
    cin>>A>>B;
    while(A!=0||B!=0){
        if(A>B)
            swap(A, B);
        int i=1;
        while(primi[i]<A)
            i++;
        for(; primi[i+2]<=B; i++){
            if(primi[i]-primi[i-1]!=primi[i+1]-primi[i]&&primi[i+1]-primi[i]==primi[i+2]-primi[i+1]){
                i++;
                if(primi[i+1]-primi[i]==primi[i+2]-primi[i+1]){
                    if(primi[i+2]<=B)
                        cout<<primi[i-1]<<" "<<primi[i]<<" "<<primi[i+1]<<" "<<primi[i+2]<<endl;
                }
                else
                    cout<<primi[i-1]<<" "<<primi[i]<<" "<<primi[i+1]<<endl;

            }
        }
        cin>>A>>B;
    }
}
