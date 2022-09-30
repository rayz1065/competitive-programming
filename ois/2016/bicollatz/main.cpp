#include <cstdio>
#include <iostream>

using namespace std;
int main(){
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
   int a, b, cont=0,oa,ob;
   cin>>a;
   cin>>b;
   while((a!=1||b!=1)&&cont!=-1){
       if(a%2==0&&b%2==0){
           a=a/2;
           b=b/2;
       }
       else if(a%2==1&&b%2==1){
           a=a*3+1;
           b=b*3+1;
       }
       else if(a%2==1){
           a=a+3;
       }
       else{
           b=b+3;
       }
       cont++;
       if(a==2&&b==1){
           cont==-1;
       }
       if(cont==100){
           oa=a;
           ob=b;
       }
       if(oa==a&&ob==b){
           cont=-1;
       }
   }
   cout<<cont;
}