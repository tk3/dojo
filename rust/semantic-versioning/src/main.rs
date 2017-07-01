
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
    fn version_works() {
        let v: Version = Version { major: 1, minor: 4, patch: 2 };

        assert_eq!(v.major, 1);
        assert_eq!(v.minor, 4);
        assert_eq!(v.patch, 2);
    }
}

