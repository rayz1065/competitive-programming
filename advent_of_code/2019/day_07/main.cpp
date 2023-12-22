#include <iostream>
#include <cassert>
#include <algorithm>
#include <queue>

#define MAXL 3000
#define MAX_OUTPUT 100
#define MAXN MAXL/2

using namespace std;

char input[MAXL];

int day_7_run();
int day_7_part_1();
void get_param_state(bool param_state[], int op);
int formatta_input(int dati[], char str[]);
bool skip_to_next_num(char str[], int &i);
int read_int(char str[], int &i);
bool is_digit(char c);
int prompt_for_input();
void clone_arr(int da[], int a[], int n);

struct intcode_computer{
    int n;
    int ops[MAXL/2];
    int ops_memo[MAXL/2];
    queue<int> queued_input;
    queue<int> output_data;
    int last_output = 0;
    bool return_on_output = false;
    bool return_on_missing_input = false;
    bool print_output = true;
    int curr_op = 0;
    bool is_halted = false;
    bool missing_input = true;

    intcode_computer(){}
    intcode_computer(int _ops[], int _n){
        n = _n;
        clone_arr(_ops, ops, n);
        clone_arr(ops, ops_memo, n);
    }

    void add_input(int in){
        queued_input.push(in);
        missing_input = false;
    }

    int get_val(int ops[], int target, bool state){
        if(state)
            return target;
        assert(target < n);

        return ops[target];
    }

    int interpret_op(){
        int op = ops[curr_op];
        bool param_state[3];
        get_param_state(param_state, op);
        int op_code = op % 100;

        if(op_code == 1){
            // sum
            int target = ops[curr_op + 3];
            int a = get_val(ops, ops[curr_op + 1], param_state[0]);
            int b = get_val(ops, ops[curr_op + 2], param_state[1]);

            ops[target] = a + b;
            return curr_op + 4;
        }
        else if(op_code == 2){
            // product
            int target = ops[curr_op + 3];
            int a = get_val(ops, ops[curr_op + 1], param_state[0]);
            int b = get_val(ops, ops[curr_op + 2], param_state[1]);

            ops[target] = a * b;
            return curr_op + 4;
        }
        else if(op_code == 3){
            // input
            int target = ops[curr_op + 1];
            assert(target < n);
            if(return_on_missing_input && !has_queued_inputs()){
                missing_input = true;
                return curr_op;
            }
            ops[target] = get_input();
            return curr_op + 2;
        }
        else if(op_code == 4){
            // output
            int target = get_val(ops, ops[curr_op + 1], param_state[0]);
            output(target);
            return curr_op + 2;
        }
        else if(op_code == 5){
            // jump-if-true
            int check = get_val(ops, ops[curr_op + 1], param_state[0]);
            int go_to = get_val(ops, ops[curr_op + 2], param_state[1]);

            if(check != 0){
                return go_to;
            }
            return curr_op + 3;
        }
        else if(op_code == 6){
            // jump-if-false
            int check = get_val(ops, ops[curr_op + 1], param_state[0]);
            int go_to = get_val(ops, ops[curr_op + 2], param_state[1]);

            if(check == 0)
                return go_to;
            return curr_op + 3;
        }
        else if(op_code == 7){
            // less than
            int a = get_val(ops, ops[curr_op + 1], param_state[0]);
            int b = get_val(ops, ops[curr_op + 2], param_state[1]);
            int target = ops[curr_op + 3];

            ops[target] = (a < b);

            return curr_op + 4;
        }
        else if(op_code == 8){
            // less than
            int a = get_val(ops, ops[curr_op + 1], param_state[0]);
            int b = get_val(ops, ops[curr_op + 2], param_state[1]);
            int target = ops[curr_op + 3];

            ops[target] = (a == b);

            return curr_op + 4;
        }
        else if(op_code == 99){
            is_halted = true;
            return curr_op + 1;
        }
        for(int i = 0; i < n; i++)
            printf("%d\t", ops[i]);
        printf("\n%d -> %d", curr_op, ops[curr_op]);
        assert(false);
    }

    int get_stored_input(){
        assert(!queued_input.empty());
        int r = queued_input.front();
        queued_input.pop();
        return r;
    }

    int get_input(){
        if(has_queued_inputs())
            return get_stored_input();
        return prompt_for_input();
    }

    bool has_queued_inputs(){
        return !queued_input.empty();
    }

    void reset_program(){
        curr_op = 0;
        clone_arr(ops_memo, ops, n);
        is_halted = false;
    }

    void output(int data){
        if(print_output)
            printf("o: %d\n", data);
        output_data.push(data);
        last_output = data;
    }

    int get_queued_output(){
        //printf("req output\n");
        assert(!output_data.empty());
        int r = output_data.front();
        output_data.pop();
        return r;
    }

    bool return_req(){
        if(!output_data.empty() && return_on_output)
            return true;
        if(missing_input && return_on_missing_input)
            return true;
        return false;
    }

    int run_program(){
        assert(!is_halted);

        while(curr_op < n && !is_halted && !return_req()){
            //printf("%d -> \n", curr_op);
            curr_op = interpret_op();
            //printf("   -> %d\n", curr_op);
        }

        if(ops[curr_op] == 99)
            is_halted = true;
        //printf("state: %d < %d, ops[%d] = %d, output_data.empty() = %d\n", curr_op, n, curr_op, ops[curr_op], output_data.empty());

        return get_queued_output();
    }

    void set_program(int _ops[], int _n){
        n = _n;
        clone_arr(_ops, ops_memo, n);
    }
};

int prompt_for_input(){
    printf("input: ");
    int t;
    scanf("%d", &t);
    return t;
}

bool is_digit(char c){
    return c >= '0' && c <= '9';
}

int read_int(char str[], int &i){
    int s = 0;
    bool neg = false;

    if(str[i] == '-')
        neg = true, i++;

    while(i < MAXL && is_digit(str[i])){
        s = (s * 10) + str[i++] - '0';
    }

    return (neg) ? -s : s;
}

bool skip_to_next_num(char str[], int &i){
    while(i < MAXL && str[i] != '\0' && !is_digit(str[i]) && str[i] != '-')
        i++;
    return (i < MAXL && str[i] != '\0');
}

int formatta_input(int dati[], char str[]){
    int i = 0, c = 0;

    while(skip_to_next_num(str, i)){
        dati[c++] = read_int(str, i);
    }

    return c;
}

void get_param_state(bool param_state[], int op){
    for(int i = 0; i < 3; i++)
        param_state[i] = false;

    if(op >= 10000)
        param_state[2] = true, op-= 10000;
    if(op >= 1000)
        param_state[1] = true, op-= 1000;
    if(op >= 100)
        param_state[0] = true;
}

bool is_day_7 = true;
int day_7_curr_test[5];
bool day_7_output_used = true;
int day_7_curr_data = 0;

void clone_arr(int da[], int a[], int n){
    for(int i = 0; i < n; i++)
        a[i] = da[i];
}

intcode_computer day_7_computers[5];

int day_7_run_part_1(){
    for(int i = 0; i < 5; i++)
        day_7_computers[i].reset_program();

    for(int i = 0; i < 5; i++)
        day_7_computers[i].add_input(day_7_curr_test[i]);
    day_7_computers[0].add_input(0);

    int r = day_7_computers[0].run_program();
    for(int i = 1; i < 5; i++){
        day_7_computers[i].add_input(r);
        r = day_7_computers[i].run_program();
    }

    return r;
}

int day_7_run_part_2(){
    for(int i = 0; i < 5; i++)
        day_7_computers[i].reset_program();

    for(int i = 0; i < 5; i++)
        day_7_computers[i].add_input(day_7_curr_test[i]);

    int r = 0;
    while(!day_7_computers[4].is_halted){
        for(int i = 0; i < 5; i++){
            day_7_computers[i].add_input(r);
            r = day_7_computers[i].run_program();
        }
    }
    return r;
}

int day_7_part_2(){
    for(int i = 0; i < 5; i++)
        day_7_curr_test[i] = i + 5, day_7_computers[i].return_on_missing_input = true;
    int max_r = day_7_run_part_2();
    while(next_permutation(day_7_curr_test, day_7_curr_test + 5))
        max_r = max(day_7_run_part_2(), max_r);

    return max_r;
}

int day_7_part_1(){
    for(int i = 0; i < 5; i++)
        day_7_curr_test[i] = i;

    int max_r = day_7_run_part_1();
    while(next_permutation(day_7_curr_test, day_7_curr_test + 5))
        max_r = max(day_7_run_part_1(), max_r);

    return max_r;
}

int ops[MAXL];

int main(){
    cin.getline(input, MAXL);
    int n;
    n = formatta_input(ops, input);

    if(is_day_7){
        for(int i = 0; i < 5; i++)
            day_7_computers[i].set_program(ops, n);
        //printf("max_r = %d\n", day_7_part_1());
        printf("max_r = %d\n", day_7_part_2());
    }
    else{
        intcode_computer a = intcode_computer(ops, n);
        printf("ultimo output: %d\n", a.run_program());
    }
}
