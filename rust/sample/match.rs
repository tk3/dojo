fn main() {
    sample1();
    sample2();
}

fn sample1() -> () {
    println!("sample 1");

    for n in 0..10 {
        let r = match n {
          0           => 1,
          t @ 2       => t + 10,
          n if n < 5  => 5,
          _           => 6
        };
        println!("{} -> {}", n, r);
    }
}

fn sample2() -> () {
    println!("sample 2");

    for n in 0..3 {
        let r = match n {
          t @ 2 => {
              let a = t + 10;
              a
          },
          _     => 6
        };
        println!("{} -> {}", n, r);
    }
}

