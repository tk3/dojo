use std::collections::HashMap;

fn main() {
    let mut h = HashMap::new();

    h.insert("aaa", 100);
    h.insert("bbb", 200);
    h.insert("ccc", 300);

    let v1 = h.get(&"aaa");
    assert_eq!(Some(&100), v1);
    assert_eq!(&100, v1.unwrap());

    let v2 = h.get(&"www");
    assert_eq!(None, v2);

    match h.get(&"bbb") {
        Some(&val) => println!("exist: {}", val),
         _ => println!("not found"),
    }

    for (key, &val) in h.iter() {
        println!(">> {}: {}", key, val);
    }
}

