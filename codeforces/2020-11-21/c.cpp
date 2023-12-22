#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n, k;

char a[MAXN], b[MAXN];

int countA[30], countB[30];

void init(){
    cin >> n >> k;
    cin >> a >> b;

    fill(countA, countA + 30, 0);
    fill(countB, countB + 30, 0);
}

bool solve(){
    for(int i = 0; i < n; i++)
        countA[a[i] - 'a']++, countB[b[i] - 'a']++;

    for(int i = 0; i < 26; i++){
        if(countA[i] < countB[i])
            return false;
        else if(countA[i] > countB[i]){
            int diff = countA[i] - countB[i];
            if(diff%k == 0)
                countA[i + 1]+= diff, countA[i]-= diff;
            else
                return false;
        }
    }
    return true;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<(solve() ? "Yes" : "No")<<"\n";
    }
}
