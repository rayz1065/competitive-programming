#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int N, S=0;
    in>>N;
    vector<unsigned long long int> usernames;
    unsigned long long int setdiIn=0;
    string input;
    for(int i=0; i<N; i++){
        in>>input;
        setdiIn=0;
        for(int c=0; c<input.size(); c++){
            if(input[c]<=60)
                setdiIn=setdiIn|((long long int)1<<((int)input[c]-48));
            else
                setdiIn=setdiIn|((long long int)1<<((int)input[c]-87));
        }
        for(int c=0; c<usernames.size(); c++){
                if((usernames[c]&setdiIn)==setdiIn)
                    S++;
                if((usernames[c]&setdiIn)==usernames[c])
                    S++;
        }
        usernames.push_back(setdiIn);
        setdiIn=0;
    }
    out<<S;
}