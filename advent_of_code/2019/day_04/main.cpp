#include <bits/stdc++.h>

using namespace std;

int min_val, max_val;

int to_chr(int a, char *chr_num){
    if(a == 0){
        chr_num[0] = '0';
        chr_num[1] = '\0';
        return 1;
    }
    int e = 0;
    while(a > 0){
        chr_num[e++] = a%10 + '0';
        a/= 10;
    }
    chr_num[e] = '\0';
    reverse(chr_num, chr_num + e);
    return e;
}

bool has_repeated_digit(char *chr_num, int l){
    for(int i = 1; i < l; i++)
        if(chr_num[i] == chr_num[i - 1])
            return true;
    return false;
}

bool has_pair_of_repeating_digits(char *chr_num, int l){
    int repeats = 1;
    for(int i = 1; i < l; i++){
        if(chr_num[i] == chr_num[i - 1])
            repeats++;
        else{
            if(repeats == 2)
                return true;
            repeats = 1;
        }
    }
    return repeats == 2;
}

bool is_not_decreasing(char *chr_num, int l){
    for(int i = 1; i < l; i++)
        if(chr_num[i] < chr_num[i - 1])
            return false;
    return true;
}

bool has_six_digits(char *chr_num, int l){
    return l == 6;
}

bool is_in_range(int a, int l){
    return (min_val < a && a < max_val);
}

bool eval_num(int a){
    char chr_num[10];
    int l = to_chr(a, chr_num);

    return has_repeated_digit(chr_num, l) && is_not_decreasing(chr_num, l);
}

bool eval_num_2(int a){
    char chr_num[10];
    int l = to_chr(a, chr_num);

    return has_pair_of_repeating_digits(chr_num, l) && is_not_decreasing(chr_num, l);
}

int parte_1(){
    int s = 0;
    for(int i = min_val; i < max_val; i++){
        if(eval_num(i))
            s++;
    }
    return s;
}

int parte_2(){
    int s = 0;
    for(int i = min_val; i < max_val; i++){
        if(eval_num_2(i))
            s++;
    }
    return s;
}

int main(){
    scanf("%d-%d", &min_val, &max_val);

    printf("Ci sono %d numeri validi nella parte 1\nCi sono %d numeri validi nella parte 2\n", parte_1(), parte_2());
}
