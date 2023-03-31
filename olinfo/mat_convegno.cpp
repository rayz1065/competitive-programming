#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int* C;
static int res;

// Declaring functions

#include <vector>
#include <stack>
#define MAXN 100005
using namespace std;

vector<int> grafo[MAXN];
int figli[MAXN];
int R = 0;

int coppie(int N, int* C){
    int capo = 0;
    for(int i = 0; i < N; i++){
        if(C[i] >= 0)
            grafo[C[i]].push_back(i);
        else
            capo = i;
    }
    stack<int> FF;
    FF.push(capo);
    while(!FF.empty()){
        int nodo = FF.top();
        FF.pop();
        if(figli[nodo] < 0){
            figli[nodo] = 0;
            for(auto i:grafo[nodo])
                figli[nodo]+= figli[i] + 1;
            R+= figli[nodo];
        }
        else{
            FF.push(nodo);
            figli[nodo] = -1;
            for(auto i:grafo[nodo]){
                FF.push(i);
            }
        }
    }
    return R;
}

int main() {
	fr = stdin;
	fw = stdout;

	// Reading input
	fscanf(fr, " %d", &N);
	C = (int*)malloc((N) * sizeof(int));
	for (int i0 = 0; i0 < N; i0++) {
		fscanf(fr, " %d", &C[i0]);
	}

	// Calling functions
	res = coppie(N, C);

	// Writing output
	fprintf(fw, "%d\n", res);

	fclose(fr);
	fclose(fw);
	return 0;
}
