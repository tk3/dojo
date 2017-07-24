extern crate regex;
use regex::Regex;

fn sample1() {
    let r = Regex::new("world");

    match r {
        Ok(n) => {
            println!("OK: {}", n);
            assert!(n.is_match("Hello, world!"))
        }
        Err(e) => println!("NG: {}", e),
    }
}

fn sample2() {
    let r = Regex::new("[[[[");

    match r {
        Ok(n) => println!("OK: {}", n),
        Err(e) => println!("NG: {}", e),
    }
}

fn main() {
    sample1();
    sample2();
}

