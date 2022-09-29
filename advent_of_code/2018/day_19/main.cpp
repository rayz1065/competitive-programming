#include <bits/stdc++.h>
#define MAXOP 40
using namespace std;

int reg[6];
int ipPointer;
int nOp = 0;

struct opNode{
    string opCode;
    int a;
    int b;
    int c;
} operazioni[MAXOP];

int leggiNumero(char stringa[], int &i){
    bool meno = false;
    int S = 0;
    while(stringa[i] != '\0' && !((stringa[i] >= '0' && stringa[i] <= '9') || stringa[i] == '-'))
        i++;
    if(stringa[i] == '-')
        meno = true, i++;
    while(stringa[i] != '\0' && ((stringa[i] >= '0' && stringa[i] <= '9')))
        S = S*10 + stringa[i++] - '0';
    return S*((meno)?-1:1);
}

int execOp(string opCode, int regA, int regB, int valA, int valB){
    if(opCode == "addr")
        return regA + regB;     /// addr
    if(opCode == "addi")
        return regA + valB;     /// addi
    if(opCode == "banr")
        return regA & regB;     /// banr
    if(opCode == "bani")
        return regA & valB;     /// bani
    if(opCode == "borr")
        return regA | regB;     /// borr
    if(opCode == "bori")
        return regA | valB;     /// bori
    if(opCode == "setr")
        return regA;            /// setr
    if(opCode == "seti")
        return valA;            /// seti
    if(opCode == "gtir")
        return valA > regB;     /// gtir
    if(opCode == "gtri")
        return regA > valB;     /// gtri
    if(opCode == "gtrr")
        return regA > regB;     /// gtrr
    if(opCode == "gtir")
        return valA == regB;    /// eqir
    if(opCode == "egri")
        return regA == valB;    /// eqri
    if(opCode == "eqrr")
        return regA == regB;     /// eqrr
    if(opCode == "mulr")
        return regA * regB;     /// mulr
    if(opCode == "muli")
        return regA * valB;     /// muli

    assert(false);
}

int main(){
    fstream in;
    in.open("input19.txt", ios::in);

    char inputTxt[100];

    int i = 0;
    in.getline(inputTxt, 100);
    ipPointer = leggiNumero(inputTxt, i);

    while(in.getline(inputTxt, 100)){
        i = 0;
        while(inputTxt[i] != ' ' && inputTxt[i] != '\0')
            operazioni[nOp].opCode+= inputTxt[i++];
        operazioni[nOp].a = leggiNumero(inputTxt, i);
        operazioni[nOp].b = leggiNumero(inputTxt, i);
        operazioni[nOp].c = leggiNumero(inputTxt, i);
        nOp++;
    }
    reg[0] = 0;
    while(reg[ipPointer] >= 0 && reg[ipPointer] < nOp){
        int currOperation = reg[ipPointer];
        int a = operazioni[currOperation].a, b = operazioni[currOperation].b, c = operazioni[currOperation].c;
        reg[c] = execOp(operazioni[currOperation].opCode, reg[a], reg[b], a, b);
        reg[ipPointer]++;
        //for(int i = 0; i < 6; i++)
        //    cout<<reg[i]<<"\t";
        //cout<<endl;
    }
    cout<<reg[0];
}
