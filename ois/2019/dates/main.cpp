#include <bits/stdc++.h>
using namespace std;

char dataTxt[10];
int lMesi[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int findYear(int i, int giorno, int mese){
    int digits = 0, year = 0;
    while(dataTxt[i] != '\0'){
        year = year*10 + dataTxt[i] - '0';
        i++, digits++;
    }
    if(digits == 2 && year >= 0 && year <= 99)
        return 1;
    if(digits == 3 && year >= 900 && year <= 999)
        return 1;
    if(digits == 4 && year >= 1900 && year <= 1999)
        return 1;
    return 0;
}

int findMonth(int i, int giorni){
    int S = 0;
    int shortMonth = dataTxt[i] - '0';
    int longMonth = shortMonth*10 + dataTxt[i + 1] - '0';
    if(shortMonth > 0 && lMesi[shortMonth] >= giorni)
        S+= findYear(i + 1, giorni, shortMonth);
    if(longMonth > 0 && longMonth <= 12 && lMesi[longMonth] >= giorni)
        S+= findYear(i  + 2, giorni, longMonth);
    return S;
}

int findDay(){
    int S = 0;
    int shortDay = dataTxt[0] - '0';
    int longDay = shortDay*10 + dataTxt[1] - '0';
    if(shortDay > 0)
        S+= findMonth(1, shortDay);
    if(longDay > 0 && longDay <= 31)
        S+= findMonth(2, longDay);
    return S;
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> dataTxt;
    cout << findDay();
}
