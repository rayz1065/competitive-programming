#include <bits/stdc++.h>

using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    unsigned int num[N];
    int val[N];
    for(int i=0; i<N; i++)
        in>>num[i];

    sort(num, num+N);
    int mVal=0;
    for(int i=0; i<N; i++){
        val[i]=1;
        for(int j=i-1; j>=0; j--)
            if(num[i]%num[j]==0&&val[j]+1>val[i])
                val[i]=val[j]+1;
        mVal=max(mVal, val[i]);
    }
    out<<mVal;
}
