#include <bits/stdc++.h>
#define MAXN 1200
#define MAXG 3500
using namespace std;

string avvenimenti[MAXN];
char avv[50];
int oreSonno[MAXG];
set<int> guardie;

int main(){
    fstream in, out;
    in.open("input4_ord.txt", ios::in);

    int N = 0;
    while(in.getline(avv, 50, '\n')){
        avvenimenti[N++] = avv;
    }

    //sort(avvenimenti, avvenimenti + N);
    int guardia, guardiaMax = 0, lastGiorno = -1, lastMese = -1, addormentata = 0;
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
            addormentata = timeStamp;
            cout<<"guardia "<<guardia<<" da "<<addormentata<<" ";
        }
        if(cosa == "wakes"){
            cout<<"a "<<timeStamp<<" ("<<timeStamp - addormentata;
            oreSonno[guardia]+= timeStamp - addormentata;
            if(timeStamp - addormentata < 0){
                oreSonno[guardia]+= 24*3600;
                cout<<" + "<<24*3600;
            }
            cout<<")\n";
        }
    }

    vector<pair<int, int> > ordineOreSonno;
    for(auto i:guardie){
        ordineOreSonno.push_back({oreSonno[i], i});
    }

    sort(ordineOreSonno.begin(), ordineOreSonno.end());
    reverse(ordineOreSonno.begin(), ordineOreSonno.end());

    cout<<ordineOreSonno.begin()->second;
}
