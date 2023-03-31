#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

int main(){
    fstream in,out;
    in.open("input.txt",ios::in);
    out.open("output.txt",ios::out);
    int B, G, E;
    in>>B;
    unordered_set<string> badW;
    for(int i=0; i<B; i++){
        string word;
        in>>word;
        badW.insert(word);
    }
    in>>G;
    unordered_set<string> gudW;
    for(int i=0; i<G; i++){
        string word;
        in>>word;
        gudW.insert(word);
    }
    int spamE=0, legitE=0;
    in>>E;
    for(int i=0; i<E; i++){
        int N;
        in>>N;
        bool spam=false, legit=false;
        for(int i=0; i<N; i++){
            string word;
            in>>word;
            if(gudW.count(word))
                legit=true;
            if(badW.count(word))
                spam=true;
        }
        if(legit&&!spam)
            legitE++;
        else if(spam&&!legit)
            spamE++;
    }
    out<<spamE<<" "<<legitE;
}
