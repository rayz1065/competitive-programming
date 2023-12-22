#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
char a[MAXN];

void init(){
    cin >> n;
    cin >> a;
}

int lft(int i){
    return (i + n - 1)%n;
}

int rgt(int i){
    return (i + 1)%n;
}

bool isOnlyOneChar(){
    for(int i = 1; i < n; i++)
        if(a[i] != a[i - 1])
            return false;
    return true;
}

int getEndOfCurrentString(int i){
    while(a[rgt(i)] == a[i])
        i = rgt(i);
    return i;
}

int solve(){
    if(isOnlyOneChar())
        return (n + 2)/3;

    int s = 0, firstIdx = 0;

    while(a[firstIdx] != 'R')
        firstIdx++;
    while(a[lft(firstIdx)] == 'R')
        firstIdx = lft(firstIdx);

    // firstIdx: V
    //          LR...

    int i = firstIdx;
    do{
        int e = getEndOfCurrentString(i);
        int len = (e - i + 1 + n)%n;
        s+= len/3;
        i = rgt(e);
    } while(i != firstIdx);

    return s;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
