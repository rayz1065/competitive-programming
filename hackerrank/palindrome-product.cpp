#include <bits/stdc++.h>
using namespace std;

set<int> palindromi;

int palMax(int N){
    int S=0;
    for(auto c:palindromi){
        if(c>=N)
            return S;
        S = c;
    }
    return S;
}

bool isPalindrome(int N){
    int cifre[7];
    int numSize = 0;
    while(N>0){
        cifre[numSize++] = N%10;
        N/=10;
    }
    for(int i=0; i<numSize/2; i++)
        if(cifre[i]!=cifre[numSize-i-1])
            return false;
    return true;
}

int main(){
    int T;
    cin>>T;

    for(int i=100; i<1000; i++)
        for(int j=100; j<1000; j++)
            if(isPalindrome(i*j))
                palindromi.insert(i*j);

    for(int i=0; i<T; i++){
        int N;
        cin>>N;
        cout<<palMax(N)<<endl;
    }
}
