#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n, m, k, sum=0, t=0, dacc=0;
    cin>>n>>m>>k;
    int lampioni[n];
    for(int i=0; i<n; i++){
        cin>>lampioni[i];
        if(i<m)
            sum+=lampioni[i];
    }

    t=sum;
    for(int i=m-1; i>=0&&k-t>0; i--){
        if(lampioni[i]==0){
            lampioni[i]=1;
            t++;
        }
    }

    dacc=t-sum;
    sum=t;
    for(int i=1; i+m<=n; i++){
        sum=sum+lampioni[i-1+m]-lampioni[i-1];
        if(sum<k){
            lampioni[i+m-1]=1;
            dacc++;
            sum++;
        }
    }
    cout<<dacc;
}
