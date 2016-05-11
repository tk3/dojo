fn main() {
    use std::io::prelude::*;
    use std::net::TcpStream;
    use std::str;

    {
        let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();

        let _ = stream.write(&[1]);

        let mut line;
        line = [0; 128];
        let read_byte = stream.read(&mut line);
        match read_byte {
            Ok(n) => {
                println!("Received {} bytes", n);
                println!(">> [{}]", str::from_utf8(&line[0..n]).unwrap());
            },
            _ => {},
        }
    }
}
