#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N;
    in>>N;
    int mando[N+1], cannel[N+1];
    mando[0]=0;
    for(int i=1; i<=N; i++){
        int v;
        in>>v;
        mando[i]=mando[i-1]+v;
    }
    cannel[0]=0;
    for(int i=1; i<=N; i++){
        int v;
        in>>v;
        cannel[i]=cannel[i-1]+v;
    }
    int maxF=1;
    for(int i=0; i<N-maxF; i++){
        int j=i+maxF;
        while(j<=N){
            j++;
            while(j<=N&&cannel[j]-cannel[i]<mando[j]-mando[i]){
                if(binary_search(cannel+j, cannel+N, mando[j]-mando[i]+cannel[i]))
                    j=lower_bound(cannel+j, cannel+N, mando[j]-mando[i]+cannel[i])-cannel;
                else
                    j=upper_bound(cannel+j, cannel+N, mando[j]-mando[i]+cannel[i])-cannel;
            }
            if(j<N&&mando[j]-mando[i]<=cannel[j]-cannel[i]){
                cout<<i<<" "<<j<<" "<<cannel[i]<<" "<<cannel[j]<<" "<<mando[i]<<" "<<mando[j]<<endl;
                if(i==0)
                    maxF=max(maxF, j-i);
                else
                    maxF=max(maxF, j-i+1);
            }
        }
    }
    cout<<maxF;
}
