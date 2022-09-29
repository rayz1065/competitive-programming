#include <bits/stdc++.h>
#define MAXN 305
using namespace std;

int N = 300;
int pwGrid[MAXN][MAXN];
int sommeRighe[MAXN][MAXN];

int centinaia(int N){
    return (N/100)%10;
}

int cPower(int xMin, int yMin, int xMax, int yMax){
    int S = 0;
    for(int x = xMin; x <= xMax; x++){
        S+= sommeRighe[x][yMax] - sommeRighe[x][yMin - 1];
    }
    return S;
}

int main(){
    fstream in, out;
    in.open("input11.txt", ios::in);

    int serialNum;
    in >> serialNum;
    for(int x = 1; x <= N; x++){
        for(int y = 1; y <= N; y++){
            int rackId = x + 10;
            int power = rackId * y;
            power+= serialNum;
            power*= rackId;
            power = centinaia(power) - 5;
            pwGrid[x][y] = power;
            sommeRighe[x][y] = sommeRighe[x][y - 1] + power;
        }
    }

    int maxPower = 0, bestX, bestY, bestS;
    for(int s = 1; s <= 300; s++){
        for(int x = 1; x <= N - s + 1; x++){
            for(int y = 1; y <= N - s + 1; y++){
                int currPower = cPower(x, y, x + s - 1, y + s - 1);
                if(currPower > maxPower)
                    bestX = x, bestY = y, maxPower = currPower, bestS = s;
            }
        }
    }
    cout<<bestX<<","<<bestY<<","<<bestS<<" -> "<<maxPower<<endl;
    for(int y = max(1, bestY - 1); y < min(N, bestY + bestS + 1); y++){
        for(int x = max(1, bestX - 1); x < min(N, bestX + bestS + 1); x++){
            cout<<((pwGrid[x][y] >= 0 && pwGrid[x][y] <= 9)?" ":"")<<pwGrid[x][y]<<" ";
        }
        cout<<endl;
    }
}

// rack Id = X + 10
// power = rack ID * Y
// power+= grid serial number
// power*= rack ID
// mantenere solo la cifra delle centinaia
// power-= 5
