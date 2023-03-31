#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int input, n1=1, n2=1, succ=0;
    cin>>input;
    while(succ==0&&n1<input/2){
        n1++;
        if(input%n1==0){
            succ=1;
            input=input/n1;
        }
    }
    if(succ==0){
        cout<<(-1);
    }
    else{
        succ=0;
        while(succ==0&&n2<input/2){
            n2++;
            if(input%n2==0){
                succ=1;
                cout<<(-1);
            }
        }
        if(succ==0){
                cout<<n1<<" "<<input;
        }
    }
}
