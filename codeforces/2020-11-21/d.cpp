#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

lli d, k;

void init(){
    cin >> d >> k;
}

bool inRange(lli x, lli y){
    // cout<<x<<","<<y<<" -> "<<x*x<<" + "<<y*y<<" < "<<d*d<<"\n"<<x*x + y*y<<" < "<<d*d<<"\n"<<(x*x + y*y < d*d)<<"\n";
    if(x*x < 0 || y*y < 0 || x*x + y*y < 0 || x > d || y > d) return false; // don't judge
    return x*x + y*y <= d*d;
}

bool solve(lli x, lli y){
    // cout<<"(x,y) = ("<<x<<","<<y<<")\n";
    if(inRange(x + k, y) && !solve(x + k, y)) return true;
    if(inRange(x, y + k) && !solve(x, y + k)) return true;

    return false;
}

/*bool solve(){
    lli m = sqrt((d*d)/(2 * k * k));
    while(inRange(m*k, m*k)){
        cout<<"increase "<<m<<"\n";
        m++;
    }
    while(!inRange(m*k, m*k)){
        cout<<"too large\n";
        m--;
    }

    assert(!inRange((m + 1) * k, (m + 1)*k));

    cout<<"m = "<<m<<"\n";

    return solve(m*k, m*k);
}*/

bool solve(){
    lli lb = 0, ub = 1000000/k;

    while(ub - lb > 5){
        lli m = (lb + ub)/2;

        if(inRange(m*k, m*k))
            lb = m;
        else
            ub = m - 1;
    }

    lli m = (lb + ub)/2;
    while(inRange(m*k, m*k)){
        m++;
    }
    while(!inRange(m*k, m*k)){
        m--;
    }

    assert(!inRange((m + 1) * k, (m + 1)*k));
    assert(inRange(m*k, m*k));

    //cout<<"m = "<<m<<"\n";
    //cout<<m*k*2<<" -> "<<d*d<<"\n";

    return solve(m*k, m*k);
}

int main(){
    /*d = 50;
    k = 1;

    for(int y = d - 1; y >= 0; y--){
        for(int x = 0; x < d; x++){
            if(inRange(x, y)){
                if(x%k == 0 && y%k == 0)
                    cout<<(solve(x, y) ? "W" : "-")<<" ";
                else
                    cout<<"  ";
            }
        }
        cout<<"\n";
    }*/

    /*for(d = 10000; d < 10035; d++){
        for(k = d - 25; k <= d; k++){
            cout<<d<<" "<<k<<"\n";
            assert(solve() == solve(0ll, 0ll));
        }
    }*/

    int t;
    cin >> t;

    while(t--){
        init();
        cout<<(solve() ? "Ashish" : "Utkarsh")<<"\n";

    }

}
