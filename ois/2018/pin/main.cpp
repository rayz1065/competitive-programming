#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    unordered_map<int, pair<int, int> > freq;
    int N, K;
    cin>>N>>K;
    int pin = 0, pow10[10];
    pow10[0] = 1;
    for(int i = 0; i < K; i++){
        int S;
        cin>>S;
        pin = pin*10 + S;
    }
    for(int i = 1; i < 10; i++)
        pow10[i] = pow10[i - 1] * 10;

    int freqMax = 0, bestPin = 0;
    for(int i = K; i <= N; i++){
        if(freq[pin].second + K <= i){
            int f = ++freq[pin].first;
            freq[pin].second = i;
            if(f > freqMax){
                freqMax = f;
                bestPin = pin;
            }
        }
        if(i < N){
            int S;
            cin>>S;
            pin = (pin%pow10[K - 1])*10 + S;
        }
    }
    for(int i = K - 1; i >= 0; i--){
        int c = bestPin - bestPin%pow10[i];
        bestPin-=c;
        cout<<c/pow10[i]<<" ";
    }
}
