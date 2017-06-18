fn main() {
    let s1 = String::from("rust language!");

    println!("{}, {}", s1, s1.len());


    let mut s2 = String::from("rust");

    println!("{}, {}", s2, s2.len());

    s2.push('!');

    s2.push_str(", Golang!");

    s2.insert(0, 'a');
    s2.insert_str(2, "ok");

    println!("{}, {}", s2, s2.len());

    s2.clear();

    if s2.is_empty() {
        println!("s2 is empty.")
    }

    let s3:std::string::String = format!("{} {} {}", 1, 2, 3);
    println!("string format: {}", s3);

}
