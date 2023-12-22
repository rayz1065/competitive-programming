#include <bits/stdc++.h>
#define WIDTH 25
#define HEIGHT 6
#define MAXL 16000
#define LAYERS 100
using namespace std;

int n_pixels, n_layers, sz_layer;
char layers[LAYERS][MAXL/LAYERS + 1];

int len(char str[]){
    int i = 0;
    while(i < MAXL && str[i] != '\0')
        i++;
    return i;
}

void fill_layer(char str[], char to_str[], int l){
    for(int i = 0; i < l; i++){
        to_str[i] = str[i];
    }
    to_str[l] = '\0';
}

void fill_layers(char str[]){
    for(int i = 0; i < n_layers; i++)
        fill_layer(str + i*sz_layer, layers[i], sz_layer);
}

char input[MAXL];

int count_chr(char str[], int l, int chr){
    int s = 0;
    for(int i = 0; i < l; i++)
        if(str[i] == chr)
            s++;
    return s;
}

int part_1_calc(int i){
    return count_chr(layers[i], sz_layer, '2') * count_chr(layers[i], sz_layer, '1');
}

int part_1_find_fewest_zeros(){
    int s = count_chr(layers[0], sz_layer, '0'), b = 0;
    for(int i = 1; i < n_layers; i++)
        if(count_chr(layers[i], sz_layer, '0') < s)
            b = i, s = count_chr(layers[i], sz_layer, '0');
    return b;
}

int part_1(){
    return part_1_calc(part_1_find_fewest_zeros());
}

int part_2_find_pixel(int r, int c){
    int j = r*WIDTH + c, i = 0;

    while(i < n_layers && layers[i][j] == '2')
        i++;

    return layers[i][j];
}

char print_pixel(char c){
    if(c == '2')
        return '/';
    return (c == '1') ? 'O' : ' ';
}

void part_2(){
    printf("parte 2:\n\n");
    for(int r = 0; r < HEIGHT; r++){
        for(int c = 0; c < WIDTH; c++){
            printf("%c", print_pixel(part_2_find_pixel(r, c)));
        }
        printf("\n");
    }
}

int main(){
    fstream in;
    in.open("input.txt", ios::in);

    in.getline(input, MAXL);
    n_pixels = len(input);
    n_layers = n_pixels/(WIDTH * HEIGHT);

    printf("%d * %d * %d = %d, %d layers\n\n", WIDTH, HEIGHT, n_layers, n_pixels, n_layers);
    sz_layer = n_pixels/n_layers;

    fill_layers(input);

    printf("parte 1: %d\n\n", part_1());

    part_2();
}
