#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b){
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

long long lcm(long long a, long long b){
    return a*b/gcd(a, b);
}

long long solve(long long a, long long b){
    long long mini = min(a, b), maxi = max(a, b);
    if(maxi%mini == 0)
        return 0;

    long long dist = maxi - mini;
    if(dist == 1)
        return 0;
    long long lowestLcm = lcm(mini, maxi), bestSol = 0;
    long long f = dist - (maxi%dist);

    for(int i = 1; i <= sqrt(dist); i++){
        if(dist%i == 0){
            cout<<dist<<", "<<i<<" => "<<lcm(mini + i, maxi + i)<<" ("<<lowestLcm<<", "<<bestSol<<")\n";
            if(lcm(mini + i, maxi + i) < lowestLcm)
                lowestLcm = lcm(mini + i, maxi + i), bestSol = i;
        }
    }

    for(int i = sqrt(dist); i >= 1 ; i--){
        if(dist%i == 0){
            cout<<dist<<", "<<dist/i<<" => "<<lcm(mini + dist/i, maxi + dist/i)<<" ("<<lowestLcm<<", "<<bestSol<<")\n";
            if(lcm(mini + dist/i, maxi + dist/i) < lowestLcm)
                lowestLcm = lcm(mini + dist/i, maxi + dist/i), bestSol = dist/i;
        }
    }
    cout<<bestSol<<"\n";
    return bestSol;
}

long long brute(long long a, long long b){
    long long lowestLcm = LLONG_MAX, bestSol = -1;
    for(long long k = 0; a + k < lowestLcm; k++)
        if(lcm(a + k, b + k) < lowestLcm)
            lowestLcm = lcm(a + k, b + k), bestSol = k;
    return bestSol;
}

int main(){
    long long a, b;

    cin >> a >> b;
    /*for(a = 1; a < 20; a++){
        for(b = 1; b < 20; b++)*/
            if(solve(a, b) != brute(a, b))
                cout<<a<<","<<b<<"\t"<<solve(a, b)<<" != "<<brute(a, b)<<"\n";
    /*}*/

}
