#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
using namespace std;
int main(){
   fstream in,out;
   in.open("input.txt", ios::in);
   out.open("output.txt", ios::out);
   int N, K;
   in>>N>>K;
   int peso[N], pranzo[N][2*K+1];
   for(int i=0; i<N; i++)
       in>>peso[i];
   sort(peso, peso+N);
   int summin(peso[0]);
   bool exit=false;
   if(peso[0]>K){
       out<<peso[0];
       return 0;
   }
   for(int i=1; i<N&&!exit; i++){
       if(peso[i]<K)
           summin+=peso[i];
       else{
           exit=true;
           if(summin<K){
               out<<peso[i];
               return 0;
           }
       }
   }
   int pesomax=2*K+1;
   for(int j=0; j<pesomax; j++)
       if(peso[0]<=j)
           pranzo[0][j]=peso[0];
       else
           pranzo[0][j]=0;
   for(int i=1; i<N; i++){
       for(int j=0; j<pesomax; j++){
           if(j>=peso[i]&&peso[i]+pranzo[i-1][j-peso[i]]>pranzo[i-1][j]){
               pranzo[i][j]=peso[i]+pranzo[i-1][j-peso[i]];
           }
           else
               pranzo[i][j]=pranzo[i-1][j];
           if(pranzo[i][j]>=K)
               pesomax=j;
       }
   }
   out<<pesomax;
}