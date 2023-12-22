#include <bits/stdc++.h>
#define N_LUNE 4

using namespace std;

struct vec3{
    int x, y, z;

    vec3(int _x, int _y, int _z){
        x = _x, y = _y, z = _z;
    }

    vec3(){
        x = y = z = 0;
    }

    void print(){
        printf("<x = %d, y = %d, z = %d>\t", x, y, z);
    }

    vec3 operator + (const vec3 b) const{
        vec3 res = vec3(x + b.x, y + b.y, z + b.z);
        return res;
    }

    int sum_of_abs_values(){
        return abs(x) + abs(y) + abs(z);
    }

    bool operator == (const vec3 b) const {
        return x == b.x && y == b.y && z == b.z;
    }

    bool is_zero_vec(){
        return *this == vec3(0, 0, 0);
    }
};

int gravity_pull_on_axis(int moon_axis, int pulling_axis){
    if(pulling_axis > moon_axis)
        return +1;
    else if(pulling_axis < moon_axis)
        return -1;
    return 0;
}

vec3 gravity_pull(vec3 moon_pos, vec3 pulling_pos){
    return vec3(gravity_pull_on_axis(moon_pos.x, pulling_pos.x),
                gravity_pull_on_axis(moon_pos.y, pulling_pos.y),
                gravity_pull_on_axis(moon_pos.z, pulling_pos.z));
}

struct luna{
    vec3 posit;
    vec3 speed;

    luna(){}

    luna(int x, int y, int z){
        posit = vec3(x, y, z);
        speed = vec3(0, 0, 0);
    }

    void print(){
        printf("pos="), posit.print(), printf(", vel="), speed.print(), printf("\tpot: %d, kin: %d\n", potential_energy(), kinetic_energy());
    }

    void update_speed(luna b){
        speed = speed + gravity_pull(posit, b.posit);
    }

    void apply_speed(){
        posit = posit + speed;
    }

    int potential_energy(){
        return posit.sum_of_abs_values();
    }

    int kinetic_energy(){
        return speed.sum_of_abs_values();
    }

    int total_energy(){
        return potential_energy()*kinetic_energy();
    }

    bool operator == (const luna b) const {
        return posit == b.posit && speed == b.speed;
    }

    bool operator != (const luna b) const {
        return !(*this == b);
    }

    bool is_still(){
        return speed.is_zero_vec();
    }

    int x(){
        return posit.x;
    }

    int y(){
        return posit.y;
    }

    int z(){
        return posit.z;
    }

    int &operator[] (int index){
        assert(0 <= index && index <= 5);
        if(index == 0)
            return posit.x;
        if(index == 1)
            return posit.y;
        if(index == 2)
            return posit.z;
        if(index == 3)
            return speed.x;
        if(index == 4)
            return speed.y;
        else
            return speed.z;
    }
};

luna input_moon(){
    int x, y, z;
    while(getchar() != '<');
    assert(scanf("x=%d, y=%d, z=%d>", &x, &y, &z) == 3);

    return luna(x, y, z);
}

void iterate(luna lune[]){
    for(int i = 0; i < N_LUNE; i++){
        for(int j = 0; j < N_LUNE; j++){
            lune[i].update_speed(lune[j]);
        }
    }

    for(int i = 0; i < N_LUNE; i++){
        lune[i].apply_speed();
    }
}

void print(luna lune[]){
    for(int i = 0; i < N_LUNE; i++)
        lune[i].print();
    printf("\n");
}

int get_total_energy(luna lune[]){
    int s = 0;

    for(int i = 0; i < N_LUNE; i++)
        s+= lune[i].total_energy();

    return s;
}

bool is_still_universe(luna lune[]){
    bool all_still = true;

    for(int i = 0; i < N_LUNE; i++)
        if(!lune[i].is_still())
            all_still = false;

    return all_still;
}

void iterate_while_not_still(luna lune[], int &iteration){
    while(!is_still_universe(lune)){
        iterate(lune);
        iteration++;
    }
}

void clone_arr(luna da[], luna a[]){
    for(int i = 0; i < N_LUNE; i++)
        a[i] = da[i];
}

tuple<int, int, int, int, int, int, int, int> get_state(luna lune[], int to_find){
    tuple<int, int, int, int, int, int, int, int> s;

    get<0>(s) = lune[0][to_find];
    get<1>(s) = lune[0][to_find + 3];
    get<2>(s) = lune[1][to_find];
    get<3>(s) = lune[1][to_find + 3];
    get<4>(s) = lune[2][to_find];
    get<5>(s) = lune[2][to_find + 3];
    get<6>(s) = lune[3][to_find];
    get<7>(s) = lune[3][to_find + 3];
    // soluzioni eleganti
    return s;
}

int find_loop_on_(luna initial_state[], int to_find){
    luna lune[N_LUNE];

    int iteration = 0;

    map<tuple<int, int, int, int, int, int, int, int>, int> last_occurence;
    clone_arr(initial_state, lune);

    while(last_occurence.count(get_state(lune, to_find)) == 0){
        last_occurence[get_state(lune, to_find)] = iteration++;
        iterate(lune);
    }

    printf("ok ho trovato qualcosa a %d che avevo visto a %d\n", iteration, last_occurence[get_state(lune, to_find)]);

    return iteration;
}

int main(){
    luna lune[N_LUNE];

    for(int i = 0; i < N_LUNE; i++)
        lune[i] = input_moon();

    find_loop_on_(lune, 0);
    find_loop_on_(lune, 1);
    find_loop_on_(lune, 2);
}







