#include <bits/stdc++.h>

using namespace std;

bool willWin(int P[], int N){
    int S=P[0];
    for(int i=1; i<N; i++)
        S=S^P[i];
    return (S>0);
}

int main(){
    fstream in, out;
    out.open("output.txt", ios::out);
    srand(time(NULL));
    int N;
    cin>>N;
    while(N!=0){
        int P[N];
        for(int i=0; i<N; i++)
            cin>>P[i];
        cout<<(willWin(P, N)?"Yes":"No")<<endl;
        cin>>N;
    }
}
