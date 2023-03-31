#define MAXN 1000005
using namespace std;

bool isPrime[2 * MAXN];

void eratostene(){
    for(int i = 2; i < MAXN * 2; i++)
        isPrime[i] = true;
    for(int i = 2; i < MAXN * 2; i++){
        if(isPrime[i]){
            for(int j = i * 2; j < MAXN * 2; j+= i)
                isPrime[j] = false;
        }
    }
}

int firstNum(int N){
    int k = 2*N - 1;
    for(int j = 2; j <= 2*N; j+= 2)
        if(isPrime[k + j] && isPrime[2 + (2*N + j - 3) % (2*N)])
            return j;
}

void suddividi(int N, int* X, int* Y){
    eratostene();
    int maxP = firstNum(N);
    for(int i = 0; i < N; i++)
        X[i] = i*2 + 1, Y[i] = (2*N - i*2 + maxP - 2 - 1) % (2*N) + 1;
}