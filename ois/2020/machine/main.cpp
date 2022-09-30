#include <bits/stdc++.h>
#define MAXD 1005
#define MAXY 10005

using namespace std;

int c, d, y;
int sellat[MAXD];
int repaircost[MAXD];

int costbycycle[MAXD];
int memo[MAXY];

int solve(int yrsrem){
    if(yrsrem <= 0) return 0;

    if(memo[yrsrem] != -1) return memo[yrsrem];

    int s = INT_MAX >> 1;
    for(int i = 0; i < d && i < yrsrem; i++)
        s = min(s, costbycycle[i] + solve(yrsrem - (i + 1)));

    return memo[yrsrem] = s;
}

int costbyusingcycle(int i){
    int yrskeep = i + 1, cycles = max(0, y/yrskeep - 10);
    //cout<<"cost("<<i<<") = "<<costbycycle[i]<<" * "<<cycles<<" + "<<solve(y - cycles * yrskeep)<<" ("<<y - cycles * yrskeep<<")\n";
    return costbycycle[i] * cycles + solve(y - cycles * yrskeep);
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> c >> d >> y;
    for(int i = 0; i < d; i++)
        cin >> repaircost[i];
    for(int i = 0; i < d; i++)
        cin >> sellat[i];

    costbycycle[0] = c + repaircost[0];
    for(int i = 1; i < d; i++)
        costbycycle[i] = costbycycle[i - 1] + repaircost[i];

    for(int i = 0; i < d; i++)
        costbycycle[i]-= sellat[i];

    memset(memo, (1 << 8) - 1, sizeof memo);
    for(int i = 0; i < MAXY; i++) solve(i);

    int s = INT_MAX >> 1;
    for(int i = 0; i < d; i++)
        s = min(s, costbyusingcycle(i)); //cout<<"costo per "<<i<<": "<<costbycycle[i]<<", "<<costbyusingcycle(i)<<"\n";
    cout<<s<<"\n";
}
