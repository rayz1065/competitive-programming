#include <bits/stdc++.h>
#define MAXN 100005
#define START 1

using namespace std;

int N, K;
int houses[MAXN];

bool visited[MAXN];

int solve(){
    int curr = START, steps = 0;
    while(!visited[curr] && curr != K)
        visited[curr] = true, curr = houses[curr], steps++;
    return (curr == K) ? steps : -1;
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> K;
    for(int i = 1; i <= N; i++)
        cin >> houses[i];

    cout<<solve()<<"\n";
}
