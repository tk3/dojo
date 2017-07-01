
struct Version {
    major: i32,
    minor: i32,
    patch: i32,
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn it_works() {
        assert_eq!(0, 0);
    }
}

