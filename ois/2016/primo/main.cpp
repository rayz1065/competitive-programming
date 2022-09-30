#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define MAXprimi 10000000
bool isPrime[MAXprimi];
vector<int> primi;

void eratostene(){
    for(int i=3; i<MAXprimi; i+=2)
        isPrime[i]=true;
    primi.push_back(2);
    for(int i=3; i<MAXprimi; i+=2)
        if(isPrime[i]){
            for(int j=i*2; j<MAXprimi; j+=i)
                isPrime[j]=false;
            primi.push_back(i);
        }
}

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);

    eratostene();

    string num;
    in>>num;
    int ast=0;
    for(int i=1; i<num.size(); i++)
        if(num[i]=='*')
            ast++;

    int potenze[10];
    potenze[0]=1;
    for(int i=1; i<10; i++)
        potenze[i]=potenze[i-1]*10;
    int maxC=potenze[ast];

    int val=0;
    for(int i=0; i<num.size(); i++){
        val*=10;
        if(num[i]!='*')
            val+=(int)num[i]-48;

    }

    int S=0;
    if(isPrime[val])
        S++;

    for(int c=0; c<maxC; c++){
        for(int j=num.size()-1; j>=0; j--){
            if(num[j]=='*'){
                if((val/potenze[num.size()-1-j])%10<9){
                    val+=potenze[num.size()-1-j];
                    j=-1;
                    if(isPrime[val])
                        S++;
                }
                else
                    val-=potenze[num.size()-1-j]*9;
            }
        }
    }
    out<<S;
}
