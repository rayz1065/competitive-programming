#include <bits/stdc++.h>

using namespace std;

int main(){
    int N, M;
    cin >> N >> M;

    int chiaviPari = 0, cassePari = 0;
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        cassePari+= a%2;
    }

    for(int i = 0; i < M; i++){
        int a;
        cin >> a;
        chiaviPari+= a%2;
    }

    cout<<min(N - cassePari, chiaviPari) + min(M - chiaviPari, cassePari)<<"\n";
}
