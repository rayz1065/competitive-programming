#include <bits/stdc++.h>
#define MAXN 1000
#define OP 16
#define PARTTWO_SIZE 1000
using namespace std;

int before[MAXN][4], op[MAXN][4], after[MAXN][4], N = 0;
bool opMeans[OP][OP];
int linkOp[OP];
int partTwo[PARTTWO_SIZE][4];

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

int execOp(int opCode, int regA, int regB, int valA, int valB){
    if(opCode == 0)
        return regA + regB;     /// addr
    if(opCode == 1)
        return regA + valB;     /// addi
    if(opCode == 2)
        return regA * regB;     /// mullr
    if(opCode == 3)
        return regA * valB;     /// mulli
    if(opCode == 4)
        return regA & regB;     /// banr
    if(opCode == 5)
        return regA & valB;     /// bani
    if(opCode == 6)
        return regA | regB;     /// borr
    if(opCode == 7)
        return regA | valB;     /// bori
    if(opCode == 8)
        return regA;            /// setr
    if(opCode == 9)
        return valA;            /// seti
    if(opCode == 10)
        return valA > regB;     /// gtir
    if(opCode == 11)
        return regA > valB;     /// gtri
    if(opCode == 12)
        return regA > regB;     /// gtrr
    if(opCode == 13)
        return valA == regB;    /// eqir
    if(opCode == 14)
        return regA == valB;    /// eqri
    if(opCode == 15)
        return regA == regB;     /// eqrr
    assert(false);
}

int findOpCodes(int opCode, int regA, int regB, int regOut, int valA, int valB){
    int possibleOpCodes = 0;
    for(int op = 0; op < OP; op++){
        if(execOp(op, regA, regB, valA, valB) == regOut){
            possibleOpCodes++;
        }
        else
            opMeans[opCode][op] = false;
    }
    return possibleOpCodes;
}

void clearOp(){
    int opTot = 1000;
    while(opTot > OP){
        for(int i = 0; i < OP; i++){
            opTot = 0;
            for(int j = 0; j < OP; j++)
                opTot+= opMeans[i][j];
            if(opTot == 1){
                int j = 0;
                while(j < OP && !opMeans[i][j])
                    j++;
                for(int c = 0; c < OP; c++)
                    if(c != i)
                        opMeans[c][j] = false;
            }
        }
        opTot = 0;
        for(int i = 0; i < OP; i++){
            for(int j = 0; j < OP; j++)
                opTot+= opMeans[i][j];
        }
    }
    for(int i = 0; i < OP; i++){
        int j = 0;
        while(j < OP && !opMeans[i][j])
            j++;
        linkOp[i] = j;
    }
}

int main(){
    fstream in;
    in.open("input16.txt", ios::in);

    char inputTxt[100];
    int reg[4] = {};

    int S = 0, nOp = 0;
    memset(opMeans, 1, sizeof(int)*OP*OP);

    while(in.getline(inputTxt, 100)){
        if(inputTxt[0] == 'B'){
            int i = 0;
            for(int j = 0; j < 4; j++)
                before[N][j] = leggiNumero(inputTxt, i);
            in.getline(inputTxt, 100);
            i = 0;
            for(int j = 0; j < 4; j++)
                op[N][j] = leggiNumero(inputTxt, i);
            in.getline(inputTxt, 100);
            assert(inputTxt[0] == 'A');
            i = 0;
            for(int j = 0; j < 4; j++)
                after[N][j] = leggiNumero(inputTxt, i);
            in.getline(inputTxt, 100);
            N++;
        }
        else{
            int i = 0;
            for(int j = 0; j < 4; j++)
                partTwo[nOp][j] = leggiNumero(inputTxt, i);
            nOp++;
        }
    }

    for(int i = 0; i < N; i++){
        int a = op[i][1], b = op[i][2], c = op[i][3];
        if(findOpCodes(op[i][0], before[i][a], before[i][b], after[i][c], a, b) >= 3)
            S++;
    }
    cout<<N<<" "<<S<<"\nOperazioni da fare = "<<nOp<<endl<<endl;

    clearOp();

    for(int i = 0; i < nOp; i++){
        int opCode = linkOp[partTwo[i][0]], a = partTwo[i][1], b = partTwo[i][2], c = partTwo[i][3];
        reg[c] = execOp(opCode, reg[a], reg[b], a, b);
    }
    cout<<reg[0]<<endl;
}
