#include <bits/stdc++.h>
#define MAXN 400005

using namespace std;
int N;
int peso[MAXN];
vector<int> grafo[MAXN];
int dp[MAXN][2];
bool solved[MAXN][2];
vector<int> soluzione;

int solve(int nodo, int padre, int preso){
  if(solved[nodo][preso]) return dp[nodo][preso];
  int S = peso[nodo] * preso;
  for(auto i:grafo[nodo])
    if(i != padre){
      if(preso)
        S+= min(solve(i, nodo, 1), solve(i, nodo, 0));
      else
        S+= solve(i, nodo, 1);
    }
  solved[nodo][preso] = true;
  dp[nodo][preso] = S;
  return S;
}

void stampa(int nodo, int padre, int preso){
  if(preso)
    soluzione.emplace_back(nodo);
  for(auto i:grafo[nodo])
    if(i != padre){
      if(preso){
        if(dp[i][1] < dp[i][0]){
          stampa(i, nodo, 1);
        }
        else{
          stampa(i, nodo, 0);
        }
      }
      else{
        stampa(i, nodo, 1);
      }
    }
}

int main(){
  fstream in, out;
  in.open("input.txt", ios::in);
  out.open("output.txt", ios::out);

  in>>N;
  for(int i = 0; i < N; i++)
    in>>peso[i + 1];

  for(int i = 0; i < N - 1; i++){
    int a, b;
    in>>a>>b;
    grafo[a].push_back(b);
    grafo[b].push_back(a);
  }

    solve(1, 0, 0);
    solve(1, 0, 1);
    vector<int> S;
    if(dp[1][0] < dp[1][1]){
      stampa(1, 0, 0);
    }
    else
      stampa(1, 0, 1);
    out<<soluzione.size()<<endl;
    for(auto i:soluzione)
      out<<i<<" ";
}
