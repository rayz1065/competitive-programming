#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;

int arr[MAXN];

int main(){
    long long N, M, K;

    cin >> N >> M >> K;

    for(int i = 0; i < N; i++)
        cin >> arr[i];

    sort(arr, arr + N);

    long long maxVal = arr[N - 1], maxSVal = arr[N - 2];
    long long S = 0;

    long long cicli = M/(K + 1);

    S+= cicli*(maxVal*K + maxSVal);
    S+= (M - cicli*(K + 1))*maxVal;

    cout<<S<<"\n";
}
