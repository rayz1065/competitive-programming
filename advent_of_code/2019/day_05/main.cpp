#include <iostream>
#include <cassert>
#define MAXL 3000

using namespace std;

char input[MAXL];
int ops[MAXL/2];

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

int get_val(int ops[], int target, bool state){
    if(state)
        return target;
    return ops[target];
}

int interpret_op(int ops[], int n, int curr_op){
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

        printf("input: ");
        scanf("%d", &ops[target]);
        return curr_op + 2;
    }
    else if(op_code == 4){
        // output
        int target = get_val(ops, ops[curr_op + 1], param_state[0]);
        printf("o-%d: %d\n", curr_op, target);
        return curr_op + 2;
    }
    else if(op_code == 5){
        // jump-if-true
        int check = get_val(ops, ops[curr_op + 1], param_state[0]);
        int go_to = get_val(ops, ops[curr_op + 2], param_state[1]);

        if(check != 0)
            return go_to;
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
    cerr << "unknown op_code " << op_code << "\n";
    assert(false);
}

int main(){
    cin.getline(input, MAXL);
    int n = formatta_input(ops, input);

    int curr_op = 0;
    while(curr_op < n && ops[curr_op] != 99){
        curr_op = interpret_op(ops, n, curr_op);
    }
}
