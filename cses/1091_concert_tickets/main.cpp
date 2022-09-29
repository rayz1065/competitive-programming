#include <bits/stdc++.h>
using namespace std;

map<int, int> tickets;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin>>N>>M;

    for(int i = 0; i < N; i++){
        int t;
        cin>>t;
        tickets[t]++;
    }

    for(int i = 0; i < M; i++){
        int c;
        cin>>c;
        auto ticket = tickets.upper_bound(c);
        if(ticket != tickets.begin()){
            --ticket;
            cout<<(ticket->first)<<endl;
            ticket->second--;
            if(ticket->second == 0)
                tickets.erase(ticket);
        }
        else
            cout<<"-1\n";
    }
}
