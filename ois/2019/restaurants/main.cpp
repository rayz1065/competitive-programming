#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

int muffin[MAXN];
int punti[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin>>N;

    int S = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N + 1; j++){
            int v;
            cin>>v;
            if(i != j)
                punti[i]+= v;
        }
        if(punti[i] > punti[S])
            S = i;
        cout<<S + 1<<endl;
    }
}
