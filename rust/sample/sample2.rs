fn main() {
    let s = b"Hello, world";
    let mut buf: Vec<u8> = Vec::new();

    println!("{}", s[0]);

    let a: u8 = 0x72;

    buf.push(a);
    println!("{:?}", buf);
}
