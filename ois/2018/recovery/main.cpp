#include <bits/stdc++.h>

using namespace std;

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int T, S, Q;
    in>>T>>S>>Q;
    map<vector<int>, int> tests;

    for(int i=0; i<T; i++){
        vector<int> answers(Q);
        for(int i=0; i<Q; i++)
            in>>answers[i];

        sort(answers.begin(), answers.begin() + Q);
        tests[answers]++;
    }

    int pairs = 0;
    for(int i=0; i<S; i++){
        vector<int> studentAnswers(Q);
        for(int i=0; i<Q; i++)
            in>>studentAnswers[i];

        sort(studentAnswers.begin(), studentAnswers.begin() + Q);
        pairs+= tests[studentAnswers];
    }
    out<<pairs;
}
