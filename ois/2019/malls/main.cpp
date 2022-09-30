#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int malls[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin>>N>>K;

    for(int i = 0; i < N; i++)
        cin>>malls[i + 1];

    sort(malls + 1, malls + N + 1);
    malls[0] = -malls[1]; /// se il posto migliore è 0
    malls[N + 1] = (K - malls[N]) + K; /// se il posto migliore è K

    int maxDist = 0, bestPos = 0;

    for(int i = 1; i <= N + 1; i++){
        if(malls[i] - malls[i - 1] > maxDist){
            maxDist = malls[i] - malls[i - 1];
            bestPos = (malls[i] + malls[i - 1])/2;
        }
    }

    cout<<bestPos;
}
