
struct Version {
    major: i32,
    minor: i32,
    patch: i32,
}

impl Version {
    pub fn to_string(&self) -> String {
        format!("{}.{}.{}", self.major, self.minor, self.patch)
    }
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

    #[test]
    fn version_to_string_works() {
        let v: Version = Version { major: 1, minor: 4, patch: 2 };

        assert_eq!(v.to_string(), "1.4.2");
    }
}

