#include <bits/stdc++.h>

using namespace std;

int readNum(char str[], int &i){
    while(i < 1000 && str[i] != '\0' && (str[i] < '0' || str[i] > '9'))
        i++;
    int S = 0;
    while(i < 1000 && str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
        S = S*10 + str[i++] - '0';
    return S;
}

/// slashing bludgeoning cold radiation fire
char types [5][15] = {"slashing", "bludgeoning", "cold", "radiation", "fire"};

bool compString(const char *A, const char *B){
    for(int i = 0; i < 15 && B[i] != '\0' && A[i] != '\0'; i++)
        if(A[i] != B[i])
            return false;
    return true;
}

int getType(char str[], int &i){
    while(i < 1000 && str[i] != '\0' && str[i] != ')' && str[i] != ';'){
        for(int j = 0; j < 5; j++){
            if(compString(str + i, types[j])){
                return j;
            }
        }
        i++;
    }
    return -1;
}

struct unitsNode{
    int units;
    int hp;
    int ad;
    bool weakto[6];
    bool immuneto[6];
    int initiative;
    bool isInfection;
};

int main(){
    fstream in, out;
    in.open("input24.txt", ios::in);

    char inputTxt[1000];
    bool isInfection = false;
    while(in.getline(inputTxt, 1000)){
        if(strlen(inputTxt) < 20){
            if(strcmp(inputTxt, "Infection:") == 0)
                isInfection = true;
        }
        else{
            int i = 0;
            int units = readNum(inputTxt, i);
            int hp = readNum(inputTxt, i);
            cout<<((isInfection)?"Infection: ":"Immune sy: ")<<units<<" units, "<<hp<<" hp\n";
            while(i < 1000 && inputTxt[i] != '\0' && inputTxt[i] != '(' && strcmp(inputTxt + i, "weak") < 0)
                i++;
            if(inputTxt[i] == '('){
                i++;
                if(compString(inputTxt + i, "weak to ")){
                    int weakTo = getType(inputTxt, i);
                    while(weakTo >= 0){
                        cout<<"Weak to "<<types[weakTo]<<endl;
                        i++;
                        weakTo = getType(inputTxt, i);
                    }
                }
                if(inputTxt[i] != ')'){
                    int immuneTo = getType(inputTxt, i);
                    while(immuneTo >= 0){
                        cout<<"Immune to "<<types[immuneTo]<<endl;
                        i++;
                        immuneTo = getType(inputTxt, i);
                    }
                }
            }
            assert(i < 1000 && inputTxt[i] != '\0');
        }
    }
}
