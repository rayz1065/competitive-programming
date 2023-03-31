#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;
int a[MAXN];

int main() {
    int t;
    cin >> t;

    while(t--) {
        string trash;
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> trash >> a[i];
        }
        sort(a, a + n);
        long long int s = 0;
        for(int i = 0; i < n; i++) {
            s+= (long long int) abs(a[i] - (i + 1));
        }
        cout << s << "\n";
    }
}