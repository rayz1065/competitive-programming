#include <iostream>
#include <fstream>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

int calcola(char perm[]){
    set<int> trovati;
    for(int i=0; i<26; i++)
        for(int j=0; j<26; j++)
            if(perm[j]==perm[i]+1)
                trovati.insert(min(j-i, 26-j+i));
    return trovati.size();
}

int main(){
    srand(time(NULL));
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    char permutazione[26];
    int N;
    in>>N;
    for(int i=0; i<26; i++)
        permutazione[i]='A'+i;
    while(calcola(permutazione)!=N)
        swap(permutazione[rand()%26], permutazione[rand()%26]);
    for(int i=0; i<26; i++)
        out<<permutazione[i];
}
