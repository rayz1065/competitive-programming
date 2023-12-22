#include <bits/stdc++.h>

using namespace std;

int calc_area(int x1, int y1, int x2, int y2){
    return (y2 - y1) * (x2 - x1);
}

int main(){
    int t;
    cin >> t;

    while(t--){
        int w, h, x, y;
        cin >> w >> h >> x >> y;
        cout<<max({calc_area(0, 0, x, h),calc_area(0, 0, w, y),calc_area(x + 1, 0, w, h),calc_area(0, y + 1, w, h)})<<"\n";

    }
}
