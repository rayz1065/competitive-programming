#include <bits/stdc++.h>
#define MAXN 1500
#define MAXS 1000
using namespace std;

int ultimo[MAXS][MAXS];
bool funzica[MAXN];

int main(){
    fstream in, out;
    in.open("input3.txt", ios::in);
    //out.open("output3.txt", ios::out);

    string idString, junk, coord, dim;
    int N = 0;
    while(in >> idString){
        N++;
        int lft = 0, top = 0, w = 0, h = 0, id = 0;
        in >> junk >> coord >> dim;

        int i;
        for(i = 1; i < idString.length(); i++)
            id = (id * 10 + idString[i] - '0');

        for(i = 0; i < coord.length() && coord[i] != ','; i++)
            lft = (lft * 10 + coord[i] - '0');

        for(i = i + 1; i < coord.length() && coord[i] != ':'; i++)
            top = (top * 10 + coord[i] - '0');

        for(i = 0; i < dim.size() && dim[i] != 'x'; i++)
            w = (w * 10 + dim[i] - '0');

        for(i = i + 1; i < dim.size(); i++)
            h = (h * 10 + dim[i] - '0');

        funzica[id] = true;
        for(int i = lft; i < lft + w; i++){
            for(int j = top; j < top + h; j++){
                if(ultimo[i][j] != 0)
                    funzica[id] = funzica[ultimo[i][j]] = false;
                else
                    ultimo[i][j] = id;
            }
        }
    }

    for(int i = 1; i <= N; i++){
        if(funzica[i])
            cout<<i<<endl;
    }
}
