#include <iostream>
#include <cassert>
#include <algorithm>
#include <queue>
#include "computer.h"

using namespace std;

intcode_computer::intcode_computer(){};
intcode_computer::intcode_computer(long long _ops[], int _n){
    n = _n;
    clone_arr(_ops, ops, n);
    clone_arr(ops, ops_memo, n);
}

void intcode_computer::add_input(long long in){
    queued_input.push(in);
    missing_input = false;
}

long long intcode_computer::get_val(long long ops[], long long target, int state){
    if(state == 1)
        return target;
    if(state == 2)
        target+= rel_base;
    assert(target >= 0);
    assert(target < MAXN);

    return ops[target];
}

int intcode_computer::get_pos(long long ops[], int target, int state){
    assert(state != 1);

    if(state == 2)
        target+= rel_base;
    assert(target >= 0);
    assert(target < MAXN);

    return target;
}

long long intcode_computer::interpret_op(){
    int op = ops[curr_op];
    int param_state[3];
    get_param_state(param_state, op);
    int op_code = op % 100;

    if(op_code == 1){
        // sum
        int target = get_pos(ops, ops[curr_op + 3], param_state[2]);
        long long a = get_val(ops, ops[curr_op + 1], param_state[0]);
        long long b = get_val(ops, ops[curr_op + 2], param_state[1]);

        ops[target] = a + b;
        return curr_op + 4;
    }
    else if(op_code == 2){
        // product
        int target = get_pos(ops, ops[curr_op + 3], param_state[2]);
        long long a = get_val(ops, ops[curr_op + 1], param_state[0]);
        long long b = get_val(ops, ops[curr_op + 2], param_state[1]);

        ops[target] = a * b;
        return curr_op + 4;
    }
    else if(op_code == 3){
        // input
        int target = get_pos(ops, ops[curr_op + 1], param_state[0]);

        if(return_on_missing_input && !has_queued_inputs()){
            missing_input = true;
            return curr_op;
        }
        ops[target] = get_input();
        return curr_op + 2;
    }
    else if(op_code == 4){
        // output
        long long a = get_val(ops, ops[curr_op + 1], param_state[0]);
        output(a);
        return curr_op + 2;
    }
    else if(op_code == 5){
        // jump-if-true
        long long check = get_val(ops, ops[curr_op + 1], param_state[0]);
        int go_to = get_val(ops, ops[curr_op + 2], param_state[1]);

        if(check != 0){
            return go_to;
        }
        return curr_op + 3;
    }
    else if(op_code == 6){
        // jump-if-false
        long long check = get_val(ops, ops[curr_op + 1], param_state[0]);
        int go_to = get_val(ops, ops[curr_op + 2], param_state[1]);

        if(check == 0)
            return go_to;
        return curr_op + 3;
    }
    else if(op_code == 7){
        // less than
        int target = get_pos(ops, ops[curr_op + 3], param_state[2]);
        long long a = get_val(ops, ops[curr_op + 1], param_state[0]);
        long long b = get_val(ops, ops[curr_op + 2], param_state[1]);

        ops[target] = (a < b);

        return curr_op + 4;
    }
    else if(op_code == 8){
        // equals
        int target = get_pos(ops, ops[curr_op + 3], param_state[2]);
        long long a = get_val(ops, ops[curr_op + 1], param_state[0]);
        long long b = get_val(ops, ops[curr_op + 2], param_state[1]);

        ops[target] = (a == b);

        return curr_op + 4;
    }
    else if(op_code == 9){
        // set relative base
        long long a = get_val(ops, ops[curr_op + 1], param_state[0]);

        rel_base+= a;

        return curr_op + 2;
    }
    else if(op_code == 99){
        is_halted = true;
        return curr_op + 1;
    }
    for(int i = 0; i < n; i++)
        cout<<ops[i]<<"\t";
    cout<<"\n"<<curr_op<<" -> "<<ops[curr_op]<<"\n";
    assert(false);
}

long long intcode_computer::get_stored_input(){
    assert(!queued_input.empty());
    long long r = queued_input.front();
    queued_input.pop();
    return r;
}

long long intcode_computer::get_input(){
    if(has_queued_inputs())
        return get_stored_input();
    return prompt_for_input();
}

bool intcode_computer::has_queued_inputs(){
    return !queued_input.empty();
}

bool intcode_computer::has_queued_outputs(){
    return !output_data.empty();
}

void intcode_computer::reset_program(){
    curr_op = 0;
    clone_arr(ops_memo, ops, n);
    is_halted = false;
    rel_base = 0;
    while(!queued_input.empty())
        queued_input.pop();
    while(!output_data.empty())
        output_data.pop();
}

void intcode_computer::output(long long data){
    if(print_output)
        cout<<"o: "<<data<<"\n";
    output_data.push(data);
    last_output = data;
}

long long intcode_computer::get_queued_output(){
    assert(!output_data.empty());
    long long r = output_data.front();
    output_data.pop();
    return r;
}

bool intcode_computer::return_req(){
    if(!output_data.empty() && return_on_output)
        return true;
    if(missing_input && return_on_missing_input)
        return true;
    return false;
}

void intcode_computer::run_program(){
    assert(!is_halted);

    while(curr_op < n && !is_halted && !return_req())
        curr_op = interpret_op();
}

void intcode_computer::set_program(long long _ops[], int _n){
    n = _n;
    clone_arr(_ops, ops_memo, n);
}

long long prompt_for_input(){
    cout<<"i: ";
    long long t;
    cin >> t;
    return t;
}

bool is_digit(char c){
    return c >= '0' && c <= '9';
}

long long read_int(char str[], int &i){
    long long s = 0;
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

int formatta_input(long long dati[], char str[]){
    int i = 0, c = 0;

    while(skip_to_next_num(str, i)){
        dati[c++] = read_int(str, i);
    }

    return c;
}

void get_param_state(int param_state[], int op){
    for(int i = 0; i < 3; i++)
        param_state[i] = 0;

    while(op >= 10000)
        param_state[2]++, op-= 10000;
    while(op >= 1000)
        param_state[1]++, op-= 1000;
    while(op >= 100)
        param_state[0]++, op-= 100;
}

void clone_arr(long long da[], long long a[], int n){
    for(int i = 0; i < n; i++)
        a[i] = da[i];
}

