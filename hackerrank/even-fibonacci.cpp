#include <bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    for(int i=0; i<T; i++){
        long long N;
        cin>>N;
        long long a = 1, b = 1, S = 0;
        while(a<N){
            if(a%2==0)
                S+= a;
            a+= b;
            swap(a, b);
        }
        cout<<S<<endl;
    }
}
