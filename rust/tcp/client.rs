use std::net::TcpStream;
use std::io::prelude::*;
use std::str;

fn main() {
    let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();

    let _ = stream.write(b"OkOkOk");

    let _ = read_n_bytes(stream, 10 as u64);
}

fn read_n_bytes(stream: TcpStream, limit: u64) -> u64 {
    let mut buf = [0; 10];

    let mut handle = stream.take(limit);
    let read_byte = handle.read(&mut buf);
    match read_byte {
        Ok(n) => {
            println!("client) Received {} bytes", n);
            println!("client) >> [{}]", str::from_utf8(&buf[0..n]).unwrap());
            return n as u64;
        },
        _ => {
            return 0;
        },
    }
}
