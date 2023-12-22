#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin>>T;
    pair<int, int> test[T];
    long long soluz[T];

    for(int i=0; i<T; i++){
        int N;
        cin>>N;
        test[i] = {N, i};
    }
    sort(test, test + T);

    int aggiungi[]={3, 2, 1, 3, 1, 2, 3};
    int i = 0, j = 0;
    long long S = 0;
    while(j<T){
        for(int c=0; c<7; c++){
            while(j<T && i>=test[j].first)
                soluz[test[j++].second] = S;
            S+= i;
            i+= aggiungi[c];
        }
    }

    for(int i=0; i<T; i++)
        cout<<soluz[i]<<endl;
}
