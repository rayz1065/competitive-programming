#include <bits/stdc++.h>
#define MAXN 1200
#define MAXG 3500
using namespace std;

string avvenimenti[MAXN];
char avv[50];
int notte[120];

int main(){
    fstream in, out;
    in.open("input4_ord.txt", ios::in);
    /// guardia 2663

    int N = 0;
    while(in.getline(avv, 50, '\n')){
        avvenimenti[N++] = avv;
    }

    //sort(avvenimenti, avvenimenti + N);
    int guardia = 2663, addormentata = 0;
    for(int i = 0; i < N; i++){
        int year = 0, month = 0, day = 0, hour = 0, minute = 0;
        int j = 1;
        for(j = 1; j < avvenimenti[i].length() && avvenimenti[i][j] != '-'; j++)
            year = (year * 10 + avvenimenti[i][j] - '0');
        for(j = j + 1; j < avvenimenti[i].length() && avvenimenti[i][j] != '-'; j++)
            month = (month * 10 + avvenimenti[i][j] - '0');
        for(j = j + 1; j < avvenimenti[i].length() && avvenimenti[i][j] != ' '; j++)
            day = (day * 10 + avvenimenti[i][j] - '0');
        for(j = j + 1; j < avvenimenti[i].length() && avvenimenti[i][j] != ':'; j++)
            hour = (hour * 10 + avvenimenti[i][j] - '0');
        for(j = j + 1; j < avvenimenti[i].length() && avvenimenti[i][j] != ']'; j++)
            minute = (minute * 10 + avvenimenti[i][j] - '0');

        int timeStamp = minute + 60 * (hour + 24*(day));
        int nightStamp = ((hour + 1)%24)*60 + minute;

        string cosa = "";

        for(j = j + 2; j < avvenimenti[i].length() && avvenimenti[i][j] != ' '; j++)
            cosa+= avvenimenti[i][j];

        if(cosa == "Guard"){
            guardia = 0;
            for(j = j + 2; j < avvenimenti[i].length() && avvenimenti[i][j] != ' '; j++)
                guardia = guardia * 10 + avvenimenti[i][j] - '0';
        }
        if(cosa == "falls"){
            addormentata = nightStamp;
        }
        if(cosa == "wakes" && guardia == 2663){
            for(int i = addormentata; i < nightStamp; i++)
                notte[i]++;
        }
    }

    int notteMax = *max_element(notte, notte + 120);

    for(int i = 0; i < 120; i++){
        if(notte[i] == notteMax){
            cout<<(i%60)*2663<<endl;
        }
    }
}
