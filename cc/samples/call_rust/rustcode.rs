#![crate_type = "dylib"]

#[no_mangle]
pub extern fn sayGreeting() {
   println!("Hello, world.");
}

#[no_mangle]
pub extern fn rust_add(x: i32, y: i32) -> i32 { x + y }

