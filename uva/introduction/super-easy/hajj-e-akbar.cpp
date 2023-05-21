#include <iostream>
#define ALT 2
using namespace std;

int main(){
    string cases[]={"Hajj", "Umrah", "Akbar", "Asghar"};
    string input;
    cin>>input;
    for(int c=1; input!="*"; c++){
        for(int i=0; i<ALT; i++)
            if(input==cases[i])
                cout<<"Case "<<c<<": Hajj-e-"<<cases[i+ALT]<<endl;
        cin>>input;
    }
}
