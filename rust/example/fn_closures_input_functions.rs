fn call_function<F: Fn()>(f: F) {
    f()
}

fn print() {
    println!("I'm a function!")
}

fn main() {
    let closure = || println!("I'm a closure!");

    call_function(closure);
    call_function(print);
}
