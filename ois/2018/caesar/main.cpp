#include <bits/stdc++.h>
#define alf 26
using namespace std;

string cifr(string word){
    int diff=word[0]-'a';
    for(int i=0; i<word.size(); i++)
        word[i]=(word[i]-diff-'a'+alf)%alf+'a';
    return word;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N, M;
    in>>N>>M;
    unordered_map<string, int> freq;
    int fMax=0;
    for(int i=0; i<N; i++){
        string word;
        in>>word;
        word=cifr(word);
        freq[word]++;
        fMax=max(fMax, freq[word]);
    }
    out<<fMax;
}
