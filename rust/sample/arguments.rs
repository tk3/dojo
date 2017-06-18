use std::env;

fn main() {
    println!("{}", env::args().count());

    for a in env::args() {
        println!("{}", a);
    }

    let args: Vec<String> = env::args().collect();
    println!("program name: {}", args[0]);
}
