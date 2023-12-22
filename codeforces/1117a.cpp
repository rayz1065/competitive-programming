#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int arr[MAXN];

int main(){
    int N;

    cin >> N;

    for(int i = 0; i < N; i++)
        cin >> arr[i];

    int maxVal = *max_element(arr, arr + N);

    int c = 0, S = 0;
    for(int i = 0; i < N; i++){
        if(arr[i] == maxVal)
            c++;
        else
            c = 0;
        S = max(S, c);
    }

    cout<<S<<"\n";
}
