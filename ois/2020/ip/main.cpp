#include <bits/stdc++.h>

using namespace std;

struct ipadd{
    int ot[4];

    void scan(){
        for(int i = 0; i < 4; i++)
            cin >> ot[i], getchar();
    }

    long long toll(){
        long long s = 0;
        for(int i = 0; i < 4; i++)
            s+= (long long) ot[i] * (1<<((3 - i)*8));
        return s;
    }
};

int main(){
    ipadd a, b;
    a.scan();
    b.scan();
    cout<<b.toll() - a.toll() + 1<<"\n";
}
