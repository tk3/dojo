use std::net::TcpStream;
use std::io::prelude::*;
//use std::net::Shutdown;

fn main() {
    #[warn(unused_variables)] 
    let mut stream = TcpStream::connect("127.0.0.1:4567").unwrap();

    let request = r"GET / HTTP/1.0

";
    let _ = stream.write(request.as_bytes());

    let mut buffer = String::new();
    let _ = stream.read_to_string(&mut buffer);
    println!("{:?}", buffer);
}
