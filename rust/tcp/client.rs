fn main() {
    use std::io::prelude::*;
    use std::net::TcpStream;
    use std::str;

    {
        let mut stream = TcpStream::connect("127.0.0.1:8080").unwrap();

        //let _ = stream.write(&[1]);
        let _ = stream.write(b"OkOkOk");

        let mut line;
        line = [0; 128];
        let read_byte = stream.read(&mut line);
        match read_byte {
            Ok(n) => {
                println!("client) Received {} bytes", n);
                println!("client) >> [{}]", str::from_utf8(&line[0..n]).unwrap());
            },
            _ => {},
        }
    }
}
