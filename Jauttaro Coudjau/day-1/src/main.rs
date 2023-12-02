use std::fs::File;
use std::io::{self, prelude::*, BufReader};

fn main() -> io::Result<()> {
    let mut sum = 0;
    let file = File::open("input.txt")?;
    let reader = BufReader::new(file);

    for line in reader.lines() {
        // had "temporary value dropped while borrowed" error otherwise
        let idk_have_to_do_a_variable_will_check_the_rust_book_later = line?;
        let line_chars = idk_have_to_do_a_variable_will_check_the_rust_book_later.chars();
        let numeric_chars = line_chars.filter(|c| c.is_digit(10)).collect::<Vec<char>>();
        let first = match numeric_chars.first().expect("aled").to_digit(10) {
            Some(first) => first,
            _ => {
                println!("epic fail omg");
                continue;
            },
        };
        let last = match numeric_chars.last().expect("aled").to_digit(10) {
            Some(last) => last,
            _ => {
                println!("epic fail omg");
                continue;
            },
        };
        sum += first * 10 + last;
    }
    println!("The result for part 1 is {}", sum);
    Ok(())
}
