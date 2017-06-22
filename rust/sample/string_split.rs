fn main() {
    sample1();
    sample2();
}

fn sample2() {
    let v: Vec<&str> = "aa bb cc dd".split(' ').collect();
    println!("{:?}", v);

    assert_eq!(v, ["aa", "bb", "cc", "dd"]);
}

fn sample1() {
    let mut iter = "A few words".split_whitespace();

    assert_eq!(Some("A"), iter.next());
    assert_eq!(Some("few"), iter.next());
    assert_eq!(Some("words"), iter.next());

    assert_eq!(None, iter.next());
}

