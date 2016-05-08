
#![allow(dead_code)]

enum Person {
    Engineer,
    Scientist,
    Height(i32),
    Weight(i32),
    Info { name: String, height: i32 }
}

fn inspect(p: Person) {
    match p {
        Person::Engineer => println!("Is an engineer!"),
        Person::Scientist => println!("Is a scientist!"),
        Person::Height(i) => println!("Has a height of {}.", i),
        Person::Weight(i) => println!("Has a weght of {}.", i),
        Person::Info { name, height } => {
            println!("{} is {} tail!", name, height);
        },
    }
}

fn main() {
    let person = Person::Height(18);
    let amira = Person::Weight(10);
    let dave = Person::Info { name: "Dave".to_owned(), height: 72 };
    let revecca = Person::Scientist;
    let rohan = Person::Engineer;

    inspect(person);
    inspect(amira);
    inspect(dave);
    inspect(revecca);
    inspect(rohan);
}
