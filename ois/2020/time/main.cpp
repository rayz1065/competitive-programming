#include <bits/stdc++.h>
#define DAYHOURS 24
#define HOURMINUTES 60

using namespace std;

struct hm{
    int h;
    int m;
};

hm input_hm(){
    int h, m;
    cin >> h >> m;
    return {h, m};
}

int main(){
    hm a = input_hm(), b = input_hm();
    int sleep_hours = (b.h - a.h + DAYHOURS)%DAYHOURS, sleep_minutes = b.m - a.m;
    if(sleep_minutes < 0)
        sleep_hours = (sleep_hours + DAYHOURS - 1)%DAYHOURS, sleep_minutes = (sleep_minutes + HOURMINUTES)%HOURMINUTES;

    cout<<sleep_hours<<" "<<sleep_minutes<<"\n";
}
