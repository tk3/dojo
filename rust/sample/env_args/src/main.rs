use std::env;

fn main() {
    for arg in env::args() {
        println!("{}", arg);
    }

    let args: Vec<String> = env::args().collect();
    println!("count: {}", args.len());
    for i in 0..args.len() {
        println!("args[{}] = {}", i, args[i]);
    }

    let n = env::args().skip(1).filter(|arg| arg.len() > 3).count();
    println!("match: {:?}", n);
}
