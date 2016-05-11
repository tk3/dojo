use std::net::{TcpListener, TcpStream};
use std::io::Read;
use std::io::Write;
use std::thread;
use std::str;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8080").unwrap();

    fn handle_client(mut stream: TcpStream) {
        let mut line;
        line = [0; 128];
        let read_byte = stream.read(&mut line);
        match read_byte {
            Ok(n) => {
                println!("server) Received {} bytes", n);
                println!("server) >> [{}]", str::from_utf8(&line[0..n]).unwrap());
            },
            _ => {},
        }
        let _ = stream.write(b"Hello");
    }

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                thread::spawn(move|| {
                    handle_client(stream);
                });
            }
            Err(e) => {
                println!("server) Error: {}", e);
            },
        }
    }

    drop(listener);
}
