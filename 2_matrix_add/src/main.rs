use std::io;

// 한 줄을 읽어 공백으로 나눈 정수 목록으로 반환
fn read_nums() -> Vec<usize> {
    let mut line = String::new();
    io::stdin().read_line(&mut line).expect("입력 오류");
    line.split_whitespace()
        .map(|s| s.parse().expect("숫자를 입력하세요"))
        .collect()
}

// rows x cols 크기의 행렬을 Vec<Vec<i32>>로 입력받음
fn read_matrix(rows: usize, cols: usize) -> Vec<Vec<i32>> {
    let mut m: Vec<Vec<i32>> = Vec::with_capacity(rows);
    for _ in 0..rows {
        let mut line = String::new();
        io::stdin().read_line(&mut line).expect("입력 오류");
        let row: Vec<i32> = line
            .split_whitespace()
            .map(|s| s.parse().expect("숫자를 입력하세요"))
            .collect();
        if row.len() != cols {
            panic!("한 줄에 {}개의 수를 입력해야 합니다", cols);
        }
        m.push(row);
    }
    m
}

fn print_matrix(m: &Vec<Vec<i32>>) {
    for row in m {
        for v in row {
            print!("{:5}", v);
        }
        println!();
    }
}

fn main() {
    println!("행렬 A의 행, 열 크기 입력:");
    let a_size = read_nums();
    println!("행렬 B의 행, 열 크기 입력:");
    let b_size = read_nums();

    if a_size != b_size {
        println!("두 행렬의 크기가 달라 더할 수 없습니다.");
        return;
    }
    let (rows, cols) = (a_size[0], a_size[1]);

    println!("행렬 A 입력 ({}x{}):", rows, cols);
    let a = read_matrix(rows, cols);
    println!("행렬 B 입력 ({}x{}):", rows, cols);
    let b = read_matrix(rows, cols);

    // 결과 행렬: 필요한 크기만큼 Vec으로 동적 할당
    let mut c: Vec<Vec<i32>> = vec![vec![0; cols]; rows];
    for i in 0..rows {
        for j in 0..cols {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    println!("A + B =");
    print_matrix(&c);
}
