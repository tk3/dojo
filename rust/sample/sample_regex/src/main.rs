extern crate regex;
use regex::Regex;

fn sample1() {
    let r = Regex::new("world");

    match r {
        Ok(n) => {
            println!("OK: {}", n);
            assert_eq!(n.is_match("Hello, world!"), true)
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

fn sample3() {
    let re = Regex::new(r"(\d{4})-(\d{2})-(\d{2})").unwrap();
    let text = "2012-03-14, 2013-01-01 and 2014-07-05";
    for cap in re.captures_iter(text) {
        println!("Month: {} Day: {} Year: {}", &cap[2], &cap[3], &cap[1]);
    }
}

fn main() {
    sample1();
    sample2();
    sample3();
}

