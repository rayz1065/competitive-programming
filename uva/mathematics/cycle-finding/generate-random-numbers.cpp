#include <bits/stdc++.h>

using namespace std;

int f(int x){
    x = x*x;
    int S = 0;

    char c[10];
    sprintf(c, "%08d\n", x);

    for(int i = 2; i < 6; i++)
        S = S*10 + c[i] - '0';
    return S;
}

bool visited[10001];

int getCicleLen(int N){
    fill(visited, visited + 10000, false);
    int found = 0;

    while(!visited[N])
        visited[N] = true, N = f(N), found++;
    return found;
}

int main(){
    int N;
    cin >> N;

    while(N != 0){
        printf("%d\n", getCicleLen(N));
        cin >> N;
    }
}
