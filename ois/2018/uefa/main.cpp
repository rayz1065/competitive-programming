#include <bits/stdc++.h>

using namespace std;
unordered_map<string, int> puntiNazione;
unordered_map<string, string> nazioneSquadra;
int N, M;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin>>N>>M;
  for(int i = 0; i < N; i++){
    string squadra, nazione;
    cin>>squadra>>nazione;
    nazioneSquadra[squadra] = nazione;
  }

  for(int i = 0; i < M; i++){
    string squadraA, squadraB;
    int goalA, goalB, puntiA = 1, puntiB = 1;
    cin>>squadraA>>squadraB>>goalA>>goalB;

    if(goalA > goalB)
      puntiA+= 3;
    else if(goalB > goalA)
      puntiB+= 3;
    else
      puntiA++, puntiB++;

    puntiNazione[nazioneSquadra[squadraA]]+= puntiA;
    puntiNazione[nazioneSquadra[squadraB]]+= puntiB;

    //cout<<endl<<nazioneSquadra[squadraA]<<" "<<puntiA<<endl<<nazioneSquadra[squadraB]<<" "<<puntiB<<"\n----------\n";
  }

  map<int, set<string> > classifica;
  for(auto i:puntiNazione)
    classifica[i.second].insert(i.first);

  for(auto i = classifica.rbegin(); i != classifica.rend(); i++){
    for(auto j:i->second){
      cout<<j<<" "<<i->first<<endl;
    }
  }
}
