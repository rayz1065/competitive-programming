int N_LUNE = 4;

class Vec3{
    int x, y, z;

    Vec3(int _x, int _y, int _z){
        x = _x;
        y = _y;
        z = _z;
    }

    Vec3(){
        x = y = z = 0;
    }

    void print(){
        //print("<x = %d, y = %d, z = %d>\t", x, y, z);
    }

    Vec3 sum(Vec3 b){
        Vec3 res = new Vec3(x + b.x, y + b.y, z + b.z);
        return res;
    }

    int sum_of_abs_values(){
        return abs(x) + abs(y) + abs(z);
    }

    boolean equals_to(Vec3 b){
        return x == b.x && y == b.y && z == b.z;
    }

    boolean is_zero_vec(){
        return x == 0 && y == 0 && z == 0;
    }
};

int gravity_pull_on_axis(int moon_axis, int pulling_axis){
    if(pulling_axis > moon_axis)
        return +1;
    else if(pulling_axis < moon_axis)
        return -1;
    return 0;
}

Vec3 gravity_pull(Vec3 moon_pos, Vec3 pulling_pos){
    return new Vec3(gravity_pull_on_axis(moon_pos.x, pulling_pos.x),
                gravity_pull_on_axis(moon_pos.y, pulling_pos.y),
                gravity_pull_on_axis(moon_pos.z, pulling_pos.z));
}

class Luna{
    Vec3 posit;
    Vec3 speed;
    color col;

    Luna(){}

    Luna(int x, int y, int z){
        posit = new Vec3(x, y, z);
        speed = new Vec3(0, 0, 0);
        col = color(255, 255, 255);
    }
    
    Luna(Vec3 _posit){
      this(_posit.x, _posit.y, _posit.z);
    }

    void print(){
        //printf("pos="), posit.print(), printf(", vel="), speed.print(), printf("\tpot: %d, kin: %d\n", potential_energy(), kinetic_energy());
    }

    void update_speed(Luna b){
        speed = speed.sum(gravity_pull(posit, b.posit));
    }

    void apply_speed(){
        posit = posit.sum(speed);
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

    boolean equals_to(Luna b){
        return posit == b.posit && speed == b.speed;
    }

    boolean is_still(){
        return speed.is_zero_vec();
    }
    
    void display(){
      fill(col);
      translate(posit.x, posit.y, posit.z);
      sphere(1);
    }
};

import java.util.Arrays;

int curr_input = 0;
ArrayList<Vec3> inputs = new ArrayList<Vec3>(Arrays.asList(new Vec3(14, 9, 14), new Vec3(9, 11, 6), new Vec3(-6, 14, -4), new Vec3(4, -4, -3)));

Luna input_moon(){
    Luna to_return = new Luna(inputs.get(curr_input));
    curr_input+= 1;
    return to_return;
}

void iterate(Luna lune[]){
    for(int i = 0; i < N_LUNE; i++){
        for(int j = 0; j < N_LUNE; j++){
            lune[i].update_speed(lune[j]);
        }
    }

    for(int i = 0; i < N_LUNE; i++){
        lune[i].apply_speed();
    }
}

void print(Luna lune[]){
    for(int i = 0; i < N_LUNE; i++)
        lune[i].print();
    println("\n");
}

int get_total_energy(Luna lune[]){
    int s = 0;

    for(int i = 0; i < N_LUNE; i++)
        s+= lune[i].total_energy();

    return s;
}

boolean is_still_universe(Luna lune[]){
    boolean all_still = true;

    for(int i = 0; i < N_LUNE; i++)
        if(!lune[i].is_still())
            all_still = false;

    return all_still;
}

Luna lune[];

void setup(){
  size(500, 500, P3D);
  lune = new Luna[N_LUNE];
  
  for(int i = 0; i < N_LUNE; i++)
      lune[i] = input_moon();
      
   camera(0.0, 70.0, 120.0, 50.0, 50.0, 0.0, 
       0.0, 1.0, 0.0);
}

void draw(){
  iterate(lune);
  
  for(int i = 0; i < N_LUNE; i++){
    
    lune[i].display();
  }
}
  
