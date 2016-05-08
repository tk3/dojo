fn main() {
    let number = Some(7);
    let letter: Option<i32> = None;
    let emotion: Option<i32> = None;

    if let Some(i) = number {
        println!("Matched {:?}!", i);
    }

    if let Some(i) = letter {
        println!("Matched {:?}!", i);
    } else {
        println!("Didn't match a number. Let's go with a letter!");
    }

    let i_like_letters = false;

    if let Some(i) = emotion {
        println!("Matched {:?}!", i);
    } else if i_like_letters {
        println!("Didn't match a number. Let's go with a letter!");
    } else {
        println!("I don't like letters. Let's go with an emotion :)!");
    }
}
