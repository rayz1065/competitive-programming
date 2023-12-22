#include <iostream>
#include <cstring>
#include <assert.h>
#define MAXL 700
#define PART_2_SIZE 600000
#define DEFAULT_PATTERN_LEN 4
#define ITERATIONS 100

using namespace std;

int len(char str[]){
    int i = 0;
    while(i < MAXL && str[i] != '\0')
        i++;
    return i;
}

int default_pattern[] = {0, 1, 0, -1};
int n;

int get_pattern(int output_num, int i){
    int pattern_len = DEFAULT_PATTERN_LEN * output_num, repeat_len = pattern_len/DEFAULT_PATTERN_LEN;
    i = i%pattern_len;

    return default_pattern[(i*DEFAULT_PATTERN_LEN)/pattern_len];
}

int get_output(char str[], int output_num){
    int s = 0;


    for(int i = 0; i < n; i++){
        s+= get_pattern(output_num, i + 1) * (str[i] - '0');
        //printf("%d*%d +\t", str[i] - '0', get_pattern(output_num, i + 1));
    }
    //printf(" = %d\n", abs(s)%10);
    return abs(s)%10;
}

void itera(char str[]){
    char *memo = (char*) malloc(sizeof(char) * MAXL);
    strcpy(memo, str);

    for(int o = 0; o < n; o++)
        memo[o] = get_output(str, o + 1) + '0';

    strcpy(str, memo);

    free(memo);
}

char input[MAXL];

int get_first_digits(char *str, int digits){
    int s = 0;

    for(int i = 0; i < MAXL && str[i] != '\0' && i < digits; i++)
        s = s * 10 + str[i] - '0';

    return s;
}

void fill_part_2(char *da, char *a, int offset, int l, int n){
    printf("l = %d\n", l);
    for(int i = 0; i < l; i++){
        a[i] = da[(i + offset)%n];
    }
    a[l] = '\0';
}

char part_2[PART_2_SIZE];

void itera_part_2(char *str, int l){
    for(int i = l - 2; i >= 0; i--){
        str[i] = (str[i + 1] - '0' + str[i] - '0')%10 + '0';
    }
}

int main(){
    cin.getline(input, MAXL);

    n = len(input);

    int iterations = ITERATIONS;

    int offset = get_first_digits(input, 7);

    int l = 10000*n - offset;

    fill_part_2(input, part_2, offset, l, n);
    for(int i = 0; i < iterations; i++)
        itera_part_2(part_2, l);

    printf("%d\n", get_first_digits(part_2, 8));
}
