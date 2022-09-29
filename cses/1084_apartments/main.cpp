#include <bits/stdc++.h>
#define MAXN 200001

using namespace std;
int appartamenti[MAXN], abitanti[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    cin>>N>>M>>K;

    for(int i = 0; i < N; i++)
        cin>>abitanti[i];
    for(int i = 0; i < M; i++)
        cin>>appartamenti[i];

    sort(abitanti, abitanti + N);
    sort(appartamenti, appartamenti + M);

    int a = 0, S = 0;
    for(int i = 0; i < N && a < M; i++){
        if(abitanti[i] <= appartamenti[a] + K && abitanti[i] >= appartamenti[a] - K)
            a++, S++;
        else if(abitanti[i] > appartamenti[a] + K)
            a++, i--;
    }
    cout<<S;
}
