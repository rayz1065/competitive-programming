#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;

int N;
int arr[MAXN], dep[MAXN];

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> N;

    for(int i = 0; i < N; i++){
        in >> arr[i] >> dep[i];
    }
    sort(arr, arr + N);
    sort(dep, dep + N);
    arr[N] = dep[N] = INT_MAX/2;

    long long S = 0;
    int curr = 1, a = 0, d = 0;
    while(a < N || d < N){
        if(arr[a] < dep[d]){
            a++;
            S+= curr;
            curr++;
        }
        else{
            d++;
            curr--;
            S+= curr;
        }
    }
    cout<<S<<endl;
}
