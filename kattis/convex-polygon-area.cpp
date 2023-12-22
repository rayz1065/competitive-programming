#include <bits/stdc++.h>
#define MAXM 105
using namespace std;

double x[MAXM], y[MAXM];

int main(){
    int N;
    cin >> N;

    for(int s = 0; s < N; s++){
        double A = 0;
        int m;
        cin >> m;
        cin >> x[0] >> y[0];
        x[m] = x[0], y[m] = y[0];
        for(int j = 1; j < m; j++){
            cin >> x[j] >> y[j];
        }
        for(int j = 1; j <= m; j++){
            A+= x[j]*y[j - 1] - x[j - 1]*y[j];
        }
        cout<<abs(A/2)<<endl;
    }
}
