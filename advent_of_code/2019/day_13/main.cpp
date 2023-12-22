#include <iostream>
#include <fstream>
#include <assert.h>
#define X_MAX 40
#define Y_MAX 30

#include "computer.h"
using namespace std;

struct game{
    intcode_computer game_computer;
    int x_max = 0, y_max = 0;
    int ball_x, ball_y;
    int ball_goto_x, ball_goto_y;
    int paddle_x, paddle_y;

    typedef enum{X_COORD, Y_COORD, TILE_ID} input_state;
    typedef enum{EMPTY, WALL, BLOCK, PADDLE, BALL} tile_type;
    char *tile_display = " |*-o";
    const int set_score_x = -1;
    vector<long long> inputs;

    bool get_the_ball_mode = false;

    tile_type mappa[X_MAX][Y_MAX];
    int curr_score = 0;

    void set_score(int new_score){
        curr_score = new_score;
    }

    void add_input(long long in){
        game_computer.add_input(in);
    }

    char last_in = 's';

    int sign(int x){
        if(x < 0)
            return -1;
        if(x > 0)
            return +1;
        return 0;
    }

    int get_input(){
        /*char in1;
        int in;

        fflush(stdin);
        printf("input: ");
        in1 = getchar();
        while(in1 != 'a' && in1 != 'd' && in1 != 's' && in1 != '\n' && in1 != 'u')
            in1 = getchar();
        if(in1 == '\n')
            in1 = last_in;
        if(in1 == 'a')
            in = -1;
        else if(in1 == 'd')
            in = 1;
        else if(in1 == 's')
            in = 0;
        else if(in1 == 'u')
            in = 2;
        last_in = in1;
        if(-1 <= in && in <= 1)
            inputs.push_back(in);*/

        return sign(ball_x - paddle_x); // i feel dumb and cheated
    }

    /*void recalc_game(){
        game_computer.reset_program();
        for(int i = 0; i < X_MAX; i++)
            for(int j = 0; j < Y_MAX; j++)
                mappa[i][j] = EMPTY;
        ball_x = ball_y = paddle_x = paddle_y = 0;
        game_computer.missing_input = false;
        for(auto i:inputs)
            game_computer.add_input(i);

        //Sleep(1000);
    }*/

    char display_tile(int x, int y){
        if(mappa[x][y] == tile_type::WALL){
            if(y == 0 && x == 0)
                return ' ';
            else if(y == 0)
                return '_';
            else
                return '|';
        }
        else
            return tile_display[mappa[x][y]];
    }

    char buf[MAXL];
    void display_game(){
        int idx = 0;

        for(int y = 0; y <= y_max; y++){
            for(int x = 0; x <= x_max; x++)
                buf[idx++] = display_tile(x, y);
            buf[idx++] = '\n';
        }
        buf[idx++] = '\0';
        system("cls");
        printf("score: %d\n\n%s\n\n\n", curr_score, buf);
    }

    game(long long ops[], int n){
        ops[0] = 2;
        game_computer = intcode_computer(ops, n);
        game_computer.return_on_missing_input = true;
        game_computer.return_on_output = true;
        game_computer.print_output = false;
        game_computer.missing_input = false;
    }

    int run(){
        input_state curr_input_type = input_state::X_COORD;
        int curr_x = 0, curr_y = 0;

        while(!game_computer.is_halted){
            game_computer.run_program();

            if(game_computer.is_halted){
                /*int l = inputs.back(), am = 0;

                if(l == 0)
                    inputs.pop_back();
                else{
                    while(inputs.size() > 0 && inputs.back() == l)
                        inputs.pop_back(), am++;
                    if(inputs.empty() || inputs.back() != 0){
                        am--;
                    }
                    else if(!inputs.empty() && inputs.back() == 0)
                        inputs.pop_back();

                    for(int i = 0; i < am; i++)
                        inputs.push_back(l);
                }

                ball_goto_x = ball_x;
                ball_goto_y = ball_y;
                recalc_game();
                get_the_ball_mode = false;*/
            }
            if(game_computer.missing_input){
                //display_game();

                int in = get_input();

                if(in >= -1 && in <= 1)
                    game_computer.add_input(in);
                /*else if(in == 2){
                    if(inputs.size() > 0)
                        inputs.pop_back();
                    recalc_game();
                }*/
            }
            if(game_computer.has_queued_outputs()){
                int curr_input = game_computer.get_queued_output();
                if(curr_input_type == input_state::X_COORD){
                    curr_x = curr_input;
                    x_max = max(x_max, curr_x);
                }
                else if(curr_input_type == input_state::Y_COORD){
                    curr_y = curr_input;
                    y_max = max(y_max, curr_y);
                }
                if(curr_input_type == input_state::TILE_ID){
                    if(curr_x == set_score_x){
                        set_score(curr_input);
                    }
                    else{
                        assert(curr_input >= 0 && curr_input <= 4);
                        tile_type new_tile = (tile_type) curr_input;

                        if(new_tile == tile_type::BALL){
                            ball_x = curr_x, ball_y = curr_y;
                        }
                        if(new_tile == tile_type::PADDLE)
                            paddle_x = curr_x, paddle_y = curr_y;

                        mappa[curr_x][curr_y] = new_tile;
                    }
                }
                curr_input_type = (input_state)((curr_input_type + 1) % 3);
            }
        }
        return curr_score;
    }
};

char input[MAXL];
long long ops[MAXN];

int main(){
    fstream in;
    in.open("input.txt");
    in.getline(input, MAXL);
    int n = formatta_input(ops, input);

    game g = game(ops, n);
    printf("score: %d\n", g.run());
}
