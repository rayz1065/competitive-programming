#include <bits/stdc++.h>
using namespace std;

bool willWin(int A, int B){
    if(A==0||B==0)
        return false;
    if(A<B)
        swap(A, B);
    int maxD=A/B;
    if(maxD>1)
        return true;
    else if(!willWin(B, A-B))
        return true;
    return false;
}

int main(){
    int A, B;
    cin>>A>>B;
    while(A!=0&&B!=0){
        cout<<(willWin(A, B)?"Stan":"Ollie")<<" wins\n";
        cin>>A>>B;
    }
}
