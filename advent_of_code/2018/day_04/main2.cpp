#include <bits/stdc++.h>
#define MAXN 1200
#define MAXG 3500
using namespace std;

string avvenimenti[MAXN];
char avv[50];
int notte[MAXG][120];
set<int> guardie;

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
            guardie.insert(guardia);
        }
        if(cosa == "falls"){
            minNightStamp = min(minNightStamp, nightStamp);
            addormentata = nightStamp;
        }
        if(cosa == "wakes"){
            for(int i = addormentata; i < nightStamp; i++)
                notte[guardia][i]++;
        }
    }
    int notteMax = 0;
    guardia = 0;
    for(auto i:guardie){
        int currMax = *max_element(notte[i], notte[i] + 120);
        if(currMax > notteMax){
            notteMax = currMax;
            guardia = i;
        }
    }
    for(int j = 0; j < 120; j++){
        if(notte[guardia][j] == notteMax){
            cout<<guardia*(j%60)<<": "<<guardia<<" "<<j<<" ("<<j%60<<")\n";
        }
    }
}
