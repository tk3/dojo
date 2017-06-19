fn main() {

    for n in 0..10 {
        let r = match n {
          0           => 1,
          t @ 2       => t + 1,
          n if n < 5  => 5,
          _           => 6
        };
        println!("{} -> {}", n, r);
    }
}

