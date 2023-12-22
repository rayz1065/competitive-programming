#include <bits/stdc++.h>
#define MAXL 1500

using namespace std;

map<pair<int, int>, pair<int, int>> mp;

char input[MAXL];

map<char, pair<int, int>> mov;

vector<pair<char, int>> wire1;
vector<pair<char, int>> wire2;

int main(){
    mov['R'] = { 1,  0};
    mov['L'] = {-1,  0};
    mov['U'] = { 0,  1};
    mov['D'] = { 0, -1};

    cin.getline(input, MAXL);

    for(int i = 0, c = 0; i < MAXL && input[i] != '\0'; i++){
        char dire = input[i++];
        int n = 0;
        while(i < MAXL && ('0' <= input[i] && input[i] <= '9')){
            n = n * 10 + (input[i] - '0');
            i++;
        }
        wire1.push_back({dire, n});
    }

    cin.getline(input, MAXL);

    for(int i = 0, c = 0; i < MAXL && input[i] != '\0'; i++){
        char dire = input[i++];
        int n = 0;
        while(i < MAXL && ('0' <= input[i] && input[i] <= '9')){
            n = n * 10 + (input[i] - '0');
            i++;
        }
        wire2.push_back({dire, n});
    }

    int x = 0, y = 0, dist = 0;
    vector<pair<int, int>> cmn;
    for(int i = 0; i < wire1.size(); i++){
        char dire = wire1[i].first;
        for(int j = 0; j < wire1[i].second; j++){
            x+= mov[dire].first, y+= mov[dire].second, dist++;

            if(mp.count({x, y}) == 0)
                mp[{x, y}] = {dist, -1};//, printf("%d %d\n", x, y);
        }
    }

    x = 0, y = 0, dist = 0;
    for(int i = 0; i < wire2.size(); i++){
        char dire = wire2[i].first;
        for(int j = 0; j < wire2[i].second; j++){
            x+= mov[dire].first, y+= mov[dire].second, dist++;

            if(mp.count({x, y}) == 0)
                mp[{x, y}] = {-1, dist};
            else if(mp[{x, y}].second == -1)
                mp[{x, y}].second = dist;

            //printf("x = %d, y = %d 1: %d, 2: %d\n", x, y, mp[{x, y}].first, mp[{x, y}].second);
            if(mp[{x, y}].first != -1 && mp[{x, y}].second != -1)
                cmn.push_back({x, y});
        }
    }

    int m = INT_MAX >> 1;
    for(auto i:cmn){
        //printf("inters %d %d: %d + %d\n", i.first, i.second, mp[i].first, mp[i].second);
        m = min(m, mp[i].first + mp[i].second);
    }

    cout<<m<<"\n";
}
