#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m, a, b, price=0;
    cin>> n>>m >>a >>b;
    double pb=double(b)/m;
    if(pb<=a){
        price+=(n/m)*b;
        n=n-(n/m)*m;
    }
    else{
        price+=a*n;
        n=0;
    }
    if(b>n*a){
        price+=a*n;
    }
    else{
        price+=b;
    }
    cout<<price;
}
