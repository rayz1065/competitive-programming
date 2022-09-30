#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int a,b,x,y, ris=0;
    cin>>a>>b>>x>>y;
    if(a>b){
        int memo=b;
        b=a;
        a=memo;
    }
    if(x>y){
        int memo=y;
        y=x;
        x=memo;
    }
    if(x<=a&&y<=b)
        ris=0;
    else if(x<=a)
        ris=x*((y-b)/2+(y-b)%2);
    else if(y<=b)
        ris=x*((y-a)/2+(y-a)%2); //ok
    else if(x<=b)
        ris=x*((y-a)/2+(y-a)%2);
    else
        ris=x*y-a*b;            //ok
    cout<<ris;
}
