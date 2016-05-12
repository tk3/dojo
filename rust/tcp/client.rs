use std::net::TcpStream;
use std::io::prelude::*;
use std::str;

fn main() {
    let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();

    let _ = stream.write(b"OkOkOk");

    let mut line;
    line = [0; 128];
    let _ = read_n_bytes(stream, &mut line);
}

fn read_n_bytes(mut stream: TcpStream, buf: &mut [u8]) -> i32 {
    let read_byte = stream.read(buf);
    match read_byte {
        Ok(n) => {
            println!("client) Received {} bytes", n);
            println!("client) >> [{}]", str::from_utf8(&buf[0..n]).unwrap());
            return n as i32;
        },
        _ => {
            return -1;
        },
    }
}
