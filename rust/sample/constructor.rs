mod foo {
    pub struct Point {
        pub x: i32,
        pub y: i32,
    }

    impl Point {
        pub fn new(x: i32, y: i32) -> Point {
            Point { x: x, y: y } // this is fine, as we're in the same module
        }
    }
}

fn main() {
    let p1 = foo::Point::new(0, 0);
    let p2 = foo::Point { x: 0, y: 0 };
}
