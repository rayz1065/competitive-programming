#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int N;
char op[105];

ll readInt(char str[105], int &i){
    ll S = 0;
    bool negative = false;

    while(i < 105 && str[i] != '\0' && str[i] < '0' || str[i] > '9')
        i++;
    if(i > 0 && str[i - 1] == '-')
        negative = true;

    while(str[i] >= '0' && str[i] <= '9')
        S = (S * 10) + str[i] - '0', i++;
    return S*(negative?-1:1);
}

ll f(ll x){
    stack<ll> curr;
    for(int i = 0; i < 105 && op[i] != '\0'; i++){
        if(op[i] != ' '){
            if(op[i] == 'x')
                curr.push(x);
            else if(op[i] == 'N')
                curr.push(N);
            else if(op[i] == '*' || op[i] == '%' || op[i] == '+'){
                ll b = curr.top();
                curr.pop();
                ll a = curr.top();
                curr.pop();
                if(op[i] == '*')
                    curr.push((a*b)%N);
                else if(op[i] == '%')
                    curr.push(a%b);
                else if(op[i] == '+')
                    curr.push((a + b)%N);
            }
            else{
                ll a = readInt(op, i);
                curr.push(a);
            }
        }
    }
    return curr.top();
}

int solve(int x){
    int t = f(x), h = f(f(x));
    while(t != h)
        t = f(t), h = f(f(h));

    int mu = 0; h = x;
    while(t != h)
        t = f(t), h = f(h), mu++;
    int lambda = 1; h = f(t);
    while(t != h)
        h = f(h), lambda++;

    return lambda;
}

bool init(int &x){
    cin >> N >> x;
    cin.ignore();
    cin.getline(op, 105);
    return (N != 0);
}

int main(){
    FILE *out = stdout;
    int x;
    while(init(x)){
        fprintf(out, "%d\n", solve(x));
    }
}
