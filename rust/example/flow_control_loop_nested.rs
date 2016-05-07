
#![allow(unreachable_code)]

fn main() {
    'outer: loop {
        println!("Enterd the outer loop");

        'inner: loop {
            println!("Enterd the inner loop");

            break 'outer;
        }

        println!("This point will nerver be rached");
    }

    println!("Existed the outer loop");
}
