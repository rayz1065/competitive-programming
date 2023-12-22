#ifndef INTCODE_COMPUTER
#define INTCODE_COMPUTER

#include <queue>
#define MAXL 30000
#define MAXN MAXL/2

long long prompt_for_input();
bool is_digit(char c);
long long read_int(char str[], int &i);
bool skip_to_next_num(char str[], int &i);
int formatta_input(long long dati[], char str[]);
void get_param_state(int param_state[], int op);
void clone_arr(long long da[], long long a[], int n);

struct intcode_computer{
    int n;
    long long ops[MAXN];
    long long ops_memo[MAXN];
    std::queue<long long> queued_input;
    std::queue<long long> output_data;
    long long last_output = 0;
    bool return_on_output = false;
    bool return_on_missing_input = false;
    bool print_output = true;
    int curr_op = 0;
    bool is_halted = false;
    bool missing_input = true;
    int rel_base = 0;

    intcode_computer();
    intcode_computer(long long _ops[], int _n);

    void add_input(long long in);
    long long get_val(long long ops[], long long target, int state);
    int get_pos(long long ops[], int target, int state);
    long long interpret_op();
    long long get_stored_input();
    long long get_input();
    bool has_queued_inputs();
    bool has_queued_outputs();
    void reset_program();
    void output(long long data);
    long long get_queued_output();
    bool return_req();
    void run_program();
    void set_program(long long _ops[], int _n);
};

#endif // INTCODE_COMPUTER
