#include <bits/stdc++.h>
#define MAXN 2005

using namespace std;
int N, M;
int altezze[MAXN][MAXN];
int dist[MAXN][MAXN];
int direI[] = {-1, 0, 1, 0}, direJ[] = {0, 1, 0, -1};

inline bool inRange(int i, int j){
  return (i >= 0 && j >= 0 && i < N && j < M);
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin>>N>>M;

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++)
      cin>>altezze[i][j];
  }

  int i = 0, j = 0, currDist = 0, oldI = -1, oldJ = -1;
  while(dist[i][j] == 0){
    dist[i][j] = ++currDist;
    int bestH = INT_MAX/2, bestDire = 0;
    for(int c = 0; c < 4; c++){
      if(inRange(i + direI[c], j + direJ[c]) && !(i + direI[c] == oldI && j + direJ[c] == oldJ)){
        int newI = i + direI[c], newJ = j + direJ[c];
        //cout<<altezze[newI][newJ]<<" "<<altezze[i][j]<<" "<<bestH<<endl;
        if(abs(altezze[newI][newJ] - altezze[i][j]) <= abs(bestH - altezze[i][j])){
          if(altezze[newI][newJ] < bestH || abs(altezze[newI][newJ] - altezze[i][j]) < abs(bestH - altezze[i][j]))
            bestH = altezze[newI][newJ], bestDire = c;
        }
      }
    }
    oldI = i, oldJ = j, i = i + direI[bestDire], j = j + direJ[bestDire];
    //cout<<oldI<<" "<<oldJ<<" -> "<<i<<" "<<j<<endl;
  }
  cout<<dist[i][j] + dist[oldI][oldJ] - 1;
}
