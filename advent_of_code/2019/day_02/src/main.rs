use std::io;

fn read(input: &mut String){
    io::stdin().read_line(input).expect("Unable to fetch input");
}

fn read_input() -> Vec<(i32, bool)>{
    let mut input = String::new();
    read(&mut input);

    let a: Vec<&str> = input.trim().split(',').collect();
    let mut s: Vec<(i32, bool)> = Vec::new();

    for num in &a {
        s.push((num.trim().parse().unwrap(), false));
    }

    s
}

fn to_str(i: usize, a: (i32, bool)) -> String{
    if a.1 {
        let mut res = "op ".to_string();
        res.push_str(i.to_string().as_str());
        res.to_string()
    }
    else if i == 1 {
        "a".to_string()
    }
    else if i == 2 {
        "b".to_string()
    }
    else {
        a.0.to_string()
    }
}

fn print_op(op: char, o: usize, i1: usize, i2: usize, a1: (i32, bool), a2: (i32, bool)){
    println!("op[ {}\t] = {} {} {}", o, to_str(i1, a1), op, to_str(i2, a2));
}

fn apply_op_code(operazioni: &mut Vec<(i32, bool)>, iter: usize) -> bool{
    if operazioni[iter].0 == 99 {
        false
    }
    else{
        let o: usize = operazioni[iter + 3].0 as usize;
        let i1: usize = operazioni[iter + 1].0 as usize;
        let i2: usize = operazioni[iter + 2].0 as usize;
        let a = operazioni[i1].0;
        let b = operazioni[i2].0;

        if operazioni[iter].0 == 1 {
            print_op('+', o, i1, i2, operazioni[i1], operazioni[i2]);
            if operazioni[o].0 != a + b {
                operazioni[o].1 = true;
            }
            operazioni[o].0 = a + b;
            true
        }
        else if operazioni[iter].0 == 2 {
            print_op('*', o, i1, i2, operazioni[i1], operazioni[i2]);
            if operazioni[o].0 != a * b {
                operazioni[o].1 = true;
            }
            operazioni[o].0 = a * b;
            true
        }
        else{
            println!("Operazione non nota");
            false
        }
    }
}

fn find_res(mut dati: Vec<(i32, bool)>) -> i32{
    let mut iter = 0;

    while apply_op_code(&mut dati, iter) {
        iter = iter + 4;
    }

    dati[0].0
}

fn find_res_input(dati: &Vec<(i32, bool)>, a:i32, b:i32) -> i32{
    let mut d = dati.clone();
    d[1].0 = a;
    d[2].0 = b;
    find_res(d)
}

fn main() {
    let dati = read_input();

    let _exp = 19690720;

    println!("{}", find_res_input(&dati, 84, 44));

    // println!("{:?}", find_input(exp, &dati));
}
