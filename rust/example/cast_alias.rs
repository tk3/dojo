type NanoSecond = u64;
type Inchi = u64;

#[allow(non_camel_case_types)]
type u64_t = u64;

#[allow(trivial_numeric_casts)]
fn main() {
    let nanoseconds: NanoSecond = 5 as u64_t;
    let inches: Inchi = 2 as u64_t;

    println!("{} nanoseconds + {} inches = {} unit?",
             nanoseconds,
             inches,
             nanoseconds + inches);
}
