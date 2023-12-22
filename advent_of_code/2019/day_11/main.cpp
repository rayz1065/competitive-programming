#include <iostream>
#include <fstream>
#include <assert.h>

#define DEBUG_MODE false
#define MAX_MAPPA 1000
#include "computer.h"

using namespace std;

typedef enum{UP, RIGHT, DOWN, LEFT} DIRE;

bool mappa[MAX_MAPPA][MAX_MAPPA];
bool colored[MAX_MAPPA][MAX_MAPPA];

struct hull_painting_bot{
    intcode_computer brain;

    int r;
    int c;
    int dire = DIRE::UP;
    int total_colored;
    int op_num;

    int mov_r[4] = {-1, 0, 1, 0};
    int mov_c[4] = {0, 1, 0, -1};

    hull_painting_bot(long long *ops, int n){
        brain = intcode_computer(ops, n);
        brain.return_on_missing_input = true;
        brain.return_on_output = true;
        brain.print_output = false;

        r = MAX_MAPPA/2;
        c = MAX_MAPPA/2;

        total_colored = 0;

        for(int i = 0; i < MAX_MAPPA; i++)
            fill(mappa[i], mappa[i] + MAX_MAPPA, false); // mappa tutta nera

        op_num = 0;
    }

    void color_panel(bool color){
        assert(in_range());
        mappa[r][c] = color;
        if(!colored[r][c])
            total_colored++, colored[r][c] = true;
    }

    void start_on_white(){
        mappa[r][c] = true;
    }

    int get_new_dire(bool to_right){
        if(to_right) return (dire + 1)%4;
        else         return (dire + 3)%4;
    }

    void turn(bool to_right){
        dire = get_new_dire(to_right);
    }

    bool in_range(){
        return (r >= 0 && c >= 0 && r < MAX_MAPPA && c < MAX_MAPPA);
    }

    void walk(int am){
        assert(dire >= 0 && dire < 4);
        r+= mov_r[dire], c+= mov_c[dire];
        assert(in_range());
    }

    bool camera_input(){
        assert(in_range());
        return mappa[r][c];
    }

    void operate(){
        while(!brain.is_halted){
            brain.run_program();
            if(brain.missing_input){
                assert(!brain.has_queued_outputs());
                brain.add_input(camera_input());
            }
            if(brain.has_queued_outputs()){
                assert(!brain.has_queued_inputs());
                if(op_num % 2 == 0){
                    bool colore = brain.get_queued_output();
                    if(DEBUG_MODE)
                        printf("coloro %d,%d di %s\n", r, c, (colore) ? "bianco" : "nero");
                    color_panel(colore);
                }
                else{
                    bool move_dire = brain.get_queued_output();
                    if(DEBUG_MODE)
                        printf("Printf cambio dire per %d: da %d a %d\n", move_dire, dire, get_new_dire(move_dire));
                    turn(move_dire);
                    walk(1);
                    if(DEBUG_MODE)
                        printf("Ora sono in %d,%d\n", r, c);
                }
                op_num++;
            }
        }
    }

    int get_colored_panels(){
        return total_colored;
    }

    int min_r = MAX_MAPPA, min_c = MAX_MAPPA, max_r = 0, max_c = 0;

    void set_bounds(){
        for(int i = 0; i < MAX_MAPPA; i++){
            for(int j = 0; j < MAX_MAPPA; j++){
                if(mappa[i][j])
                    min_r = min(min_r, i), max_r = max(max_r, i), min_c = min(min_c, j), max_c = max(max_c, j);
            }
        }
    }

    void print_bounds(){
        set_bounds();

        printf("rows: %d -> %d\ncols: %d -> %d\n\n", min_r, max_r, min_c, max_c);
    }

    void print_map(){
        set_bounds();

        for(int i = min_r; i <= max_r; i++){
            for(int j = min_c; j <= max_c; j++){
                printf("%c", mappa[i][j] ? '#' : ' ');
            }
            printf("\n");
        }
    }
};

char input[MAXL];
long long ops[MAXL];

int main(){
    fstream in;
    in.open("input.txt", ios::in);
    in.getline(input, MAXL);
    int n = formatta_input(ops, input);

    hull_painting_bot hpb = hull_painting_bot(ops, n);

    hpb.start_on_white();

    hpb.operate();

    printf("Ha colorato %d pannelli\n", hpb.get_colored_panels());

    hpb.print_bounds();

    hpb.print_map();

}
