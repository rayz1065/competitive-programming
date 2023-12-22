use std::io;
use core::cmp::max;
use core::cmp::min;

fn read(input: &mut String){
    input.clear();
    io::stdin().read_line(input).expect("Unable to fetch input");
    *input = input.trim().to_string();
}

fn read_input_line(input: &String) -> Vec<(char, i32)>{
    let a: Vec<&str> = input.trim().split(',').collect();
    let mut s: Vec<(char, i32)> = Vec::new();

    for val in &a {
        let dire: char = val.chars().next().unwrap();
        let am: i32 = val[1..].trim().parse().unwrap();
        s.push((dire, am));
    }

    s
}

fn read_input() -> Vec<Vec<(char, i32)>>{
    let mut s: Vec<Vec<(char, i32)>> = Vec::new();
    let mut input = String::new();
    read(&mut input);

    while input.len() > 3 {
        s.push(read_input_line(&input));
        read(&mut input);
    }

    s
}

fn find_wire_edges(w: &Vec<(char, i32)>, x: &mut i32, y: &mut i32) -> (i32, i32, i32, i32){
    let mut x_max = *x;
    let mut x_min = *x;
    let mut y_max = *y;
    let mut y_min = *y;

    for mov in w {
        if mov.0 == 'R' {
            *x+= mov.1;
        }
        else if mov.0 == 'L' {
            *x-= mov.1;
        }
        else if mov.0 == 'U' {
            *y+= mov.1;
        }
        else if mov.0 == 'D' {
            *y-= mov.1;
        }
        else{
            panic!();
        }
        x_max = max(x_max, *x);
        x_min = min(x_min, *x);
        y_max = max(y_max, *y);
        y_min = min(y_min, *y);
    }
    (x_min, x_max, y_min, y_max)
}

fn find_wires_edges(wrs: &Vec<Vec<(char, i32)>>, x: &i32, y: &i32){
    for wr in wrs{
        let mut end_x = *x;
        let mut end_y = *y;
        println!("{:?}", find_wire_edges(&wr, &mut end_x, &mut end_y));
    }
}

fn fill_mat_wire(mat: &mut Vec<Vec<(i32, i32)>>, x: &mut i32, y: &mut i32, w: &Vec<(char, i32)>, wr_n: &i32){
    let wr_num = *wr_n;
    let mut d = 0;
    for mov in w {
        if mov.0 == 'R' {
            for _ in 0..mov.1 {
                *x+= 1;
                d+= 1;
                if wr_num == 0 && mat[*x as usize][*y as usize].0 == 0{
                    mat[*x as usize][*y as usize].0 = d;
                }
                else if wr_num == 1 && mat[*x as usize][*y as usize].1 == 0{
                    mat[*x as usize][*y as usize].1 = d;
                }
            }
        }
        else if mov.0 == 'L' {
            for _ in 0..mov.1 {
                *x-= 1;
                d+= 1;
                if wr_num == 0 && mat[*x as usize][*y as usize].0 == 0{
                    mat[*x as usize][*y as usize].0 = d;
                }
                else if wr_num == 1 && mat[*x as usize][*y as usize].1 == 0{
                    mat[*x as usize][*y as usize].1 = d;
                }
            }
        }
        else if mov.0 == 'U' {
            for _ in 0..mov.1 {
                *y+= 1;
                d+= 1;
                if wr_num == 0 && mat[*x as usize][*y as usize].0 == 0{
                    mat[*x as usize][*y as usize].0 = d;
                }
                else if wr_num == 1 && mat[*x as usize][*y as usize].1 == 0{
                    mat[*x as usize][*y as usize].1 = d;
                }
            }
        }
        else if mov.0 == 'D' {
            for _ in 0..mov.1 {
                *y-= 1;
                d+= 1;
                if wr_num == 0 && mat[*x as usize][*y as usize].0 == 0{
                    mat[*x as usize][*y as usize].0 = d;
                }
                else if wr_num == 1 && mat[*x as usize][*y as usize].1 == 0{
                    mat[*x as usize][*y as usize].1 = d;
                }
            }
        }
        else{
            panic!();
        }
    }
}

fn fill_mat_wires(mut mat: &mut Vec<Vec<(i32, i32)>>, x: &i32, y: &i32, wrs: &Vec<Vec<(char, i32)>>){
    let mut wr_num = 0;
    for wr in wrs{
        let mut end_x = *x;
        let mut end_y = *y;
        fill_mat_wire(&mut mat, &mut end_x, &mut end_y, &wr, &wr_num);
        wr_num+= 1;
    }
}

fn abs(a: i32) -> i32{
    if a >= 0 {
        a
    }
    else{
        -a
    }
}

fn man_dist(x: i32, y: i32, x2: i32, y2: i32) -> i32{
    abs(x2 - x) + abs(y2 - y)
}

fn explore_mat(mat: &Vec<Vec<(i32, i32)>>, x_center: &i32, y_center: &i32, m: &usize, n: &usize){
    let mut dist_min = -1;

    for x in 0..*n as i32 {
        for y in 0..*m as i32 {
            if mat[x as usize][y as usize].0 > 0 && mat[x as usize][y as usize].1 > 0 {
                println!("{:?}", mat[x as usize][y as usize]);
                if dist_min == -1 {
                    dist_min = mat[x as usize][y as usize].0 + mat[x as usize][y as usize].1;
                }
                else{
                    dist_min = min(dist_min, mat[x as usize][y as usize].0 + mat[x as usize][y as usize].1);
                }
            }
        }
    }

    println!("Dist min: {}", dist_min);
}

fn main() {
    let dati = read_input();

    let x_center = 13932;
    let y_center = 14902;
    let n: usize = 28000;
    let m: usize = 19000;
    find_wires_edges(&dati, &x_center, &y_center);
    
    let mut mat = vec![vec![(0,0); m]; n];

    fill_mat_wires(&mut mat, &x_center, &y_center, &dati);

    explore_mat(&mat, &x_center, &y_center, &m, &n);
}
