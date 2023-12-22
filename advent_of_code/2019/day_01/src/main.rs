use std::io;

fn read(input: &mut String){
    io::stdin().read_line(input).expect("Unable to fetch input");
}

fn read_i32() -> Result<i32, std::num::ParseIntError>{
    let mut input = String::new();
    read(&mut input);
    input.trim().parse()
}

fn read_input() -> Vec<i32>{
    let mut s: Vec<i32> = Vec::new();
    let mut input = read_i32();

    while input.is_ok() {
        s.push(input.unwrap());
        input = read_i32();
    }

    s
}

fn max(a: i32, b: i32) -> i32{
    if a > b {
        a
    }
    else{
        b
    }
}

fn fuel_per_massa(massa: i32) -> i32{
    max(0, massa/3 - 2)
}

fn req_fuel(massa: i32) -> i32{
    if massa <= 0 {
        0
    }
    else{
        fuel_per_massa(massa) + req_fuel(fuel_per_massa(massa))
    }
}

fn solve(dati: Vec<i32>) -> i32{
    let mut s = 0;
    for massa in dati {
        s+= req_fuel(massa)
    }

    s
}

fn main() {
    let dati = read_input();

    println!("Carburante necessario: {}", solve(dati));
}
