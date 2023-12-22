#include <bits/stdc++.h>
#define MAXN 100005
#define ERAT 6000
using namespace std;

bool isPrime[ERAT];
vector<int> primi;

void eratostene(){
    for(int i = 2; i < ERAT; i++)
        isPrime[i] = true;

    for(int i = 2; i < ERAT; i++){
        if(isPrime[i]){
            cout<<i<<" ";
            for(int j = i*i; j < ERAT; j+= i)
                isPrime[j] = false;
        }
    }
}

int gcd(int a, int b){
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

int getLowestDiv(int a){
    int m = sqrt(a);
    for(int i = 2; i <= m && i < a; i++){
        if(a%i == 0)
            return i;
    }
    return a;
}

int main(){
    eratostene();
    int N;
    cin >> N;
    int a;
    for(int i = 0; i < N; i++){
        cin >> a;
        bool isCasinitic = true;
        for(int i = 1; isCasinitic && i < a; i*= 2){
            if((a | i) != a){
                isCasinitic = false;
            }
        }

        if(isCasinitic)
            cout<<a/getLowestDiv(a)<<endl;
        else{
            int l = log2(a);
            cout<<(1<<(l + 1)) - 1<<endl;
        }
    }
}
