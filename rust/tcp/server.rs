use std::net::{TcpListener, TcpStream};
use std::io::Write;
use std::thread;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:8080").unwrap();

    fn handle_client(mut stream: TcpStream) {
//    fn handle_client(stream: &mut TcpStream) {
        let _ = stream.write(b"Hello");
    }

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                thread::spawn(move|| {
                    //handle_client(&mut stream);
                    handle_client(stream);
                });
            }
            //Err(e) => { /* connection failed */ }
            Err(e) => {
                println!("Error: {}", e);
            },
        }
    }

    drop(listener);
}
