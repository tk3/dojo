
fn main() {
    let scan = std::io::stdin();

    let mut line = String::new();

    let _ = scan.read_line(&mut line);
    let vec: Vec<&str> = line.split_whitespace().collect();

    let n: i32 = vec[0].parse().unwrap_or(0);
    let m: f32 = vec[1].parse().unwrap_or(0.0);
    let k: u32 = vec[2].parse().unwrap_or(0);

    println!("{}", n);
    println!("{}", m);
    println!("{}", k);
}

