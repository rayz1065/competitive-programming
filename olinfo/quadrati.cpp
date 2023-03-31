#include <cstdio>
#include <iostream>
#include <math.h>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    double long a,b;
    cin>>a>>b;
    if(fmod(sqrt(a),1)==0)
        a=sqrt(a);
    else
        a=sqrt(a)-fmod(sqrt(a),1)+1;
    b=sqrt(b)-fmod(sqrt(b),1);
    cout<<b-a+1;
}
