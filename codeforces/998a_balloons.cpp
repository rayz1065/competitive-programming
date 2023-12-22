#include <bits/stdc++.h>

using namespace std;

int main(){
    int N;
    cin>>N;

    pair<int, int> bloon[N];
    for(int i = 0; i < N; i++){
        int a;
        cin>>a;
        bloon[i] = {a, i + 1};
    }

    if(N == 1 || (N == 2 && bloon[0].first == bloon[1].first)){
        cout<<"-1";
        return 0;
    }

    sort(bloon, bloon + N);
    cout<<1<<" "<<bloon[0].second;
}
