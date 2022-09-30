#include <bits/stdc++.h>
#define POTENZAMAX 9
#define MAXN 1005
using namespace std;

int N, M, D;
int numeri[MAXN];
int power10[POTENZAMAX];
unordered_map <int, bool> mancanti;

set<int> dv;
set<int> divisori;

void aggiungiD(int a){
    if(a < 0)
        return;
    if(divisori.count(a))
        return;
    divisori.insert(a);
    for(int i = 2; i <= sqrt(a); i++)
        if(a % i == 0){
            divisori.insert(i);
            divisori.insert(a/i);
        }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>N>>M>>D;
    power10[0] = 1;
    for(int i = 1; i < POTENZAMAX; i++)
        power10[i] = power10[i - 1] * 10;

    int evenPower = 1;
    int fivePower = 1;
    for(int i = 0; i < 30; i++)
        evenPower*= 2;
    for(int i = 0; i < 10; i++)
        fivePower*= 5;

    for(int i = 0; i < N; i++){
        cin>>numeri[i];
        mancanti[numeri[i]] = true;
        while(evenPower > 1 && numeri[i] % evenPower > 0)
            evenPower/= 2;
        while(fivePower > 1 && numeri[i] % fivePower > 0)
            fivePower/= 5;
    }
    evenPower*= 2;
    fivePower*= 5;

    dv.insert(numeri[0]);

    for(int i = 1; i < N; i++){
        if(numeri[i] > numeri[i - 1])
            dv.insert(numeri[i] - numeri[i - 1]);
        else
            dv.insert(numeri[i] - numeri[i - 1] + power10[D]);
    }
    for(auto k:dv)
        for(int m = 0; m < 10; m++)
            aggiungiD(k + m*power10[D]);

    for(auto k:divisori){
        if(k % evenPower != 0 && k % fivePower != 0){
            int curr = 0;
            cout<<k<<" -> ";
            for(int i = 1; i <= M && (N - curr) - 1 <= (M - i); i++){
                cout<<k*i<<" ";
                if(numeri[curr] == k*i % power10[D]){
                    curr++;
                    if(curr == N){
                        cout<<k;
                        return 0;
                    }
                }
                else if(k % 2 != 0 && k % 5 != 0 && mancanti.count(k*i%power10[D])){
                    i = M;
                }
            }
            cout<<endl;
        }
    }
    return 1;
}
