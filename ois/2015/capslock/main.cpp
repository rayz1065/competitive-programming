#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, lett;
    cin>>n;
    cin.clear();
    cin.ignore(1, '\n');
    char lettera[n];
    cin.getline (lettera, n+1);
    for(int i=0; i<=n; i++){
        lett=lettera[i];
        if(lett>=97&&lett<=122){
            lettera[i]=lettera[i]-32;
        }
        else if(lett>=65&&lett<=90){
            lettera[i]=lettera[i]+32;
        }
        if(i<n)(cout<<lettera[i]);
    }
}
