#include <bits/stdc++.h>
#define MAXN 21
#define MAXW 2000005

using namespace std;

int n;
int a[MAXN];

int in_set[MAXN];

bool solve(int i, int s) {
    if(i == n) {
        return s == 0;
    }

    if(in_set[i] != 0) {
        return solve(i + 1, s);
    }
    in_set[i] = 1;
    if(solve(i + 1, s + a[i])) {
        return true;
    }
    in_set[i] = -1;
    if(solve(i + 1, s - a[i])) {
        return true;
    }
    in_set[i] = 0;
    return solve(i + 1, s);
}

bool solve_all() {
    for(int i = 0; i < n; i++) {
        in_set[i] = 1;
        if(solve(0, a[i])) {
            return true;
        }
        in_set[i] = 0;
    }
    return false;
}

int main() {
    int t;
    cin >> t;

    for(int t_num = 0; t_num < t; t_num++) {
        cout << "Case #"<<t_num + 1<<":\n";
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        fill(in_set, in_set + n, 0);

        if(!solve_all()) {
            cout<<"Impossible\n";
        }
        else {
            for(int i = 0; i < n; i++) {
                if(in_set[i] == 1) {
                    cout << a[i] << " ";
                }
            }
            cout << "\n";
            for(int i = 0; i < n; i++) {
                if(in_set[i] == -1) {
                    cout << a[i] << " ";
                }
            }
            cout << "\n";
        }
    }
}