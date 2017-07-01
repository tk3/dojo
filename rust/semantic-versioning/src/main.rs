
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

impl PartialEq for Version {
    fn eq(&self, other: &Version) -> bool {
        self.major == other.major && self.minor == other.minor && self.patch == other.patch
    }
}
impl Eq for Version {}

impl std::fmt::Debug for Version {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "Version {{ major: {}, minor: {}, patch: {} }}", self.major, self.minor, self.patch)
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

    #[test]
    fn version_equals_works() {
        let v: Version = Version { major: 1, minor: 4, patch: 2 };

        assert_eq!(v, Version { major: 1, minor: 4, patch: 2 });
        assert_ne!(v, Version { major: 2, minor: 1, patch: 0 });
    }
}

