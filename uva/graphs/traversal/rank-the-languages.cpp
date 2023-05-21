#include <bits/stdc++.h>

using namespace std;

int N, H, W;
vector<vector<char>> mappa;
vector<vector<bool>> visited;
int freq[30];

void init(){
    mappa.clear();
    visited.clear();

    cin >> H >> W;
    mappa.resize(H);
    visited.resize(H);
    for(int i = 0; i < H; i++){
        mappa[i].resize(W);
        visited[i].resize(W, false);

        for(int j = 0; j < W; j++)
            cin >> mappa[i][j];
    }
    fill(freq, freq + 30, 0);
}

int movH[] = {-1, 0, 1, 0};
int movW[] = {0, 1, 0, -1};

void visita(int h, int w, char c){
    if(h < 0 || h >= H || w < 0 || w >= W || visited[h][w] || mappa[h][w] != c)
        return ;
    visited[h][w] = true;
    for(int m = 0; m < 4; m++)
        visita(h + movH[m], w + movW[m], c);
}

int main(){
    FILE *out = stdout;

    cin >> N;
    for(int t = 1; t <= N; t++){
        init();
        for(int h = 0; h < H; h++){
            for(int w = 0; w < W; w++){
                if(!visited[h][w])
                    visita(h, w, mappa[h][w]), freq[mappa[h][w] - 'a']++;
            }
        }
        vector<pair<int, int>> ordFreq;
        for(int i = 0; i < 26; i++){
            if(freq[i] > 0)
                ordFreq.push_back({-freq[i], i});
        }

        sort(ordFreq.begin(), ordFreq.end());
        fprintf(out, "World #%d\n", t);
        for(auto i:ordFreq){
            fprintf(out, "%c: %d\n", i.second + 'a', -i.first);
        }
        ordFreq.clear();
    }
}
