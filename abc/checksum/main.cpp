#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

static FILE *fr, *fw;

// Declaring variables
static int P;
static int M;
static int* C;
static int* E;


using namespace std;
#include <vector>
#include <cmath>
#define maxPrime 4000000

vector<int> primi;
bool isPrime[maxPrime];
int used[maxPrime];

void inizializza(int P, int M){
    for(int i=0; i<M; i++)
        isPrime[i]=true;

    for(int i=2; i<M; i++)
        if(isPrime[i]){
            for(int j=i*2; j<M; j+=i)
                isPrime[j]=false;
            primi.push_back(i);
        }
}

int controlla(int checksum){
    vector<int> factors;
    int c=checksum, j;
    for(j=0; j<primi.size()&&primi[j]<=sqrt(c); j++)
        if(c%primi[j]==0){
            if(used[primi[j]]!=0)
                return used[primi[j]];
            while(c%primi[j]==0)
                c/=primi[j];
            factors.push_back(primi[j]);
        }

    if(c!=1){
        if(used[c]!=0)
            return used[c];
        factors.push_back(c);
    }

    for(int i=0; i<factors.size(); i++)
        used[factors[i]]=checksum;
    return 0;
}


int main() {
	fr = stdin;
	fw = stdout;

	// Iterators used in for loops
	int i0;

	// Reading input
        fscanf(fr, "%d %d", &P, &M);
	C = (int*)malloc(P * sizeof(int));
	for (i0 = 0; i0 < P; i0++) {
            fscanf(fr, "%d", &C[i0]);
	}

	// Calling functions
        inizializza(P, M);

	E = (int*)malloc(P * sizeof(int));

        for (i0 = 0; i0 < P; i0++) {
            E[i0] = controlla(C[i0]);
        }

       	// Writing output
	for (i0 = 0; i0 < P; i0++) {
            fprintf(fw, "%d ", E[i0]);
	}
	fprintf(fw, "\n");

	fclose(fr);
	fclose(fw);
	return 0;
}

