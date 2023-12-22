#include <bits/stdc++.h>
#define MAXL 100
#define MAX_CHEM 100
using namespace std;

struct chemical;
struct ingredient;
struct recipe;

struct ingredient{
    int chem_id;
    int quantity;

    void print();
    ingredient();
    ingredient(chemical, int);
};

struct chemical{
    string name;
    int chem_id;

    void print();
    chemical();
    chemical(string _name);
    bool produce(int q);
};

long long available[MAX_CHEM];

struct recipe{
    vector<ingredient> ingredients;
    int result;
    int quantity;

    void print();
    void set_result(chemical, int);
    void add_ingredient(chemical, int);
    bool run(int times);
    bool requires_ingredient(int chem_id);
};

bool is_digit(char c){
    return (c >= '0' && c <= '9');
}

bool skip_to_next_num(char str[], int &i){
    while(i < MAXL && str[i] != '\0' && !is_digit(str[i]) && str[i] != '-')
        i++;
    return (i < MAXL && str[i] != '\0');
}

long long read_int(char str[], int &i){
    long long s = 0;
    bool neg = false;

    skip_to_next_num(str, i);

    if(str[i] == '-')
        neg = true, i++;

    while(i < MAXL && is_digit(str[i])){
        s = (s * 10) + str[i++] - '0';
    }

    return (neg) ? -s : s;
}

bool is_letter(char c){
    return (c >= 'A' && c <= 'Z');
}

string read_name(char str[], int &i){
    string s;
    while(i < MAXL && str[i] != '\0' && !is_letter(str[i]))
        i++;

    while(i < MAXL && str[i] != '\0' && is_letter(str[i]))
        s.push_back(str[i++]);

    return s;
}

void skip_spaces(char str[], int &i){
    while(i < MAXL && str[i] != '\0' && (str[i] == ' ' || str[i] == '\n'))
        i++;
}

map<string, int> chemical_list;
int n_chemicals = 1;
chemical chemicals[MAX_CHEM];
recipe recipies[MAX_CHEM];

bool resolved[MAX_CHEM];
long long to_make[MAX_CHEM];

int assign_chem_id(string name){
    if(chemical_list.count(name) == 1)
        return chemical_list[name];

    int assigned_id;
    if(name == "ORE")
        assigned_id = 0;
    else
        assigned_id = n_chemicals++;

    chemical_list[name] = assigned_id;
    chemicals[assigned_id] = chemical(name);
    return assigned_id;
}

void chemical::print(){
    cout<<chem_id<<": "<<name<<"\n";
}

bool recipe::run(int times){
    for(int i = 0; i < times; i++){
        for(auto i:ingredients){
            if(!chemicals[i.chem_id].produce(i.quantity))
                return false;
        }
        available[result]+= quantity;
    }

    return true;
}

bool chemical::produce(int q){
    if(chem_id == 0){
        if(available[chem_id] >= q){
            available[chem_id]-= q;
            return true;
        }
        return false;
    }

    while(available[chem_id] < q){
        if(!recipies[chem_id].run(1))
            return false;
    }

    available[chem_id]-= q;

    return true;
}

chemical::chemical(){}
chemical::chemical(string _name){
    name = _name;
    chem_id = assign_chem_id(name);
}

void recipe::print(){
    for(int i = 0; i < ingredients.size(); i++){
        if(i > 0)
            printf(" + ");
        ingredients[i].print();
    }

    printf(" = ");

    chemicals[result].print();

    printf("\n");
}

void recipe::set_result(chemical _result, int _quantity){
    result = _result.chem_id;
    quantity = _quantity;
}

void ingredient::print(){
    cout<<quantity<<" of "<<chemicals[chem_id].name<<" ("<<chem_id<<")\n";
}

ingredient::ingredient(chemical chem, int _quantity){
    chem_id = chem.chem_id;
    quantity = _quantity;
}

void recipe::add_ingredient(chemical to_add, int quantity){
    ingredients.push_back(ingredient(to_add, quantity));
}

void interpret_input_line(char line[]){
    int i = 0;

    recipe r;
    bool is_result = false;

    while(i < MAXL && line[i] != '\0'){
        int quantity = read_int(line, i);
        string name = read_name(line, i);

        if(quantity == 0 || name.length() < 1)
            return ;

        if(is_result)
            r.set_result(chemical(name), quantity);
        else
            r.ingredients.push_back(ingredient(name, quantity));

        skip_spaces(line, i);

        if(!is_result && i < MAXL && line[i] == '='){
            is_result = true;
        }
    }

    recipies[r.result] = r;
}

int len(char str[]){
    int i = 0;

    while(i < MAXL && str[i] != '\0')
        i++;

    return i;
}

char input[MAXL];

long long fuel_cost = 873899;
int fuel_chem_id;

vector<int> topo_sort;

void resolve(int chem_id){
    if(chem_id == 0){
        return ;
    }
    int step = recipies[chem_id].quantity;

    long long missing = to_make[chem_id] - available[chem_id];
    long long actual_to_make = missing + (step - missing%step) % step;
    long long times_to_run = actual_to_make/step;

    for(auto i:recipies[chem_id].ingredients){
        to_make[i.chem_id]+= (long long)times_to_run * i.quantity;
    }
}

bool recipe::requires_ingredient(int chem_id){
    for(auto i:ingredients)
        if(i.chem_id == chem_id)
            return true;
    return false;
}

bool can_resolve(int chem_id){
    for(int i = 0; i < n_chemicals; i++){
        if(!resolved[i] && recipies[i].requires_ingredient(chem_id)){
            return false;
        }
    }
    return true;
}

long long tot_fuel = 0;

bool iterate_part_2(){
    fill(to_make, to_make + MAX_CHEM, 0);

    to_make[fuel_chem_id] = available[0]/fuel_cost;

    if(to_make[fuel_chem_id] == 0)
        return false;

    tot_fuel+= to_make[fuel_chem_id];

    for(int i = 0; i < n_chemicals; i++)
        resolve(topo_sort[i]);

    for(int i = n_chemicals - 1; i >= 0; i--){
        int chem_id = topo_sort[i];

        if(chem_id == 0){
            available[0]-= to_make[0];
            cout<<"need "<<to_make[0]<<" ore\n";
        }
        else{
            int step = recipies[chem_id].quantity;
            long long missing = to_make[chem_id] - available[chem_id];
            long long actual_to_make = missing + (step - missing%step) % step;

            available[chem_id]+= actual_to_make - to_make[chem_id];
        }
    }

    return true;
}

void fill_topo_sort(){ // 2lazy
    fill(resolved, resolved + MAX_CHEM, false);
    bool resolved_smth = true;

    while(resolved_smth){
        resolved_smth = false;

        for(int i = 0; i < n_chemicals; i++){
            if(!resolved[i] && can_resolve(i)){
                resolved[i] = true;
                resolved_smth = true;
                topo_sort.push_back(i);
            }
        }
    }
}

int main(){
    fstream in;
    in.open("input.txt", ios::in);
    while(in.getline(input, MAXL) && len(input) > 3)
        interpret_input_line(input);

    fuel_chem_id = chemical_list["FUEL"];
    available[0] = 1000000000000;
    chemicals[fuel_chem_id].print();
    recipies[fuel_chem_id].print();

    fuel_cost = 873899;

    fill_topo_sort();

    while(iterate_part_2())
        cout<<fuel_cost<<"\n"<<"ore available: "<<available[0]<<"\ntot = "<<tot_fuel<<"\n\n";
    while(chemicals[fuel_chem_id].produce(1))
        cout<<" + 1\n", tot_fuel++;
    cout<<fuel_cost<<"\n"<<"ore available: "<<available[0]<<"\ntot = "<<tot_fuel<<"\n\n";
}
