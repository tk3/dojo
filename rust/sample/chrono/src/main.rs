extern crate chrono;

use chrono::prelude::*;

fn main() {
    println!("Hello, world!");

    let utc: DateTime<Utc> = Utc::now();
    let local: DateTime<Local> = Local::now();
    println!("utc: {:?}", utc);
    println!("local: {:?}", local);


    let tm = Utc.ymd(2017, 12, 10).and_hms(5, 15, 20);
    println!("utc: {:?}", tm);
}
