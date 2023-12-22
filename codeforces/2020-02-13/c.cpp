#include <bits/stdc++.h>
#define MAXN 1e09

using namespace std;

//char str[MAXN];
int n, m;

/*bool contains_one(int l, int r){
    for(int i = l; i <= r; i++)
        if(str[i] == '1') return true;
    return false;
}

int f(){
    int s = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            if(contains_one(i, j))
                s++;
    }
    return s;
}*/

long long sum_of_first_(int n){
    return ((long long) n * (n + 1))/2;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        cin >> n >> m;

        /*
        for(int i = 0; i < n; i++)
            str[i] = '1';
        for(int i = 0; i < n - m; i++)
            str[i] = '0';

        int ma = INT_MIN/2;

        do{
            int s = f();
            if(s >= ma){
                if(s > ma)
                    cout<<s<<"\n";
                ma = s;
                for(int i = 0; i < n; i++)
                    cout<<str[i]<<" ";
                cout<<"\n";
            }
        } while(next_permutation(str, str + n));*/

        int zeri = n - m;
        int div = m + 1;
        int s_div = zeri / div;
        int larger_div = zeri - s_div * div;
        long long s = sum_of_first_(n);

//      cout<<", "<<div - larger_div<<" of size "<<s_div<<", "<<larger_div<<" of size "<<s_div + 1<<"\n";

        s-= sum_of_first_(s_div) * (div - larger_div) + sum_of_first_(s_div + 1) * larger_div;
        cout<<s<<"\n";
    }
}
