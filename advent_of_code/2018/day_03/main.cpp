#include <bits/stdc++.h>
#define MAXN 1500
#define MAXS 1000
using namespace std;

int volte[MAXS][MAXS];

int main(){
    fstream in, out;
    in.open("input3.txt", ios::in);
    //out.open("output3.txt", ios::out);

    string junk, coord, dim;
    while(in >> junk){
        in >> junk >> coord >> dim;
        int lft = 0, top = 0, w = 0, h = 0;

        int i;
        for(i = 0; i < coord.length() && coord[i] != ','; i++)
            lft = (lft * 10 + coord[i] - '0');

        for(i = i + 1; i < coord.length() && coord[i] != ':'; i++)
            top = (top * 10 + coord[i] - '0');

        for(i = 0; i < dim.size() && dim[i] != 'x'; i++)
            w = (w * 10 + dim[i] - '0');

        for(i = i + 1; i < dim.size(); i++)
            h = (h * 10 + dim[i] - '0');

        for(int i = lft; i < lft + w; i++){
            for(int j = top; j < top + h; j++){
                volte[i][j]++;
            }
        }
    }

    int piuVolte = 0;
    for(int i = 0; i < MAXS; i++){
        for(int j = 0; j < MAXS; j++){
            piuVolte+= (volte[i][j] >= 2);
        }
    }
    cout<<piuVolte<<endl;
}
