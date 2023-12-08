use std::collections::HashMap;
use std::fs::File;
use std::io::{self, prelude::*, BufReader};
use itertools::Itertools;
use std::process::exit;

fn part1() -> io::Result<()> {
    let input = File::open("input.txt")?;
    let reader = BufReader::new(input);
    let mut sum = 0;
    for line in reader.lines() {
        let line_str = line?;
        let game_n = line_str.chars().nth(5).expect("Couldn't retrieve game number");
        let picks = line_str.split(": ").nth(1).expect("wrong split on \": \"")
                            .split("; ").map(
                                |s| s.split(", ").map(
                                    |s| s.split_once(' ').expect("wrong split on \" \"")
                                    )
                                    .map(
                                    |t| (t.1, t.0.parse::<i32>().unwrap()) as (&str, i32)
                                    ).collect_tuple().unwrap()
                                ).collect::<HashMap<i32, &str>>();
                            //.reduce(|prev, next| prev);
                            //.collect::<Vec<Vec<&str>>>();
    }
    Ok(())
}
fn main() {
    let max_rgb = [12, 13, 14];
    let _ = part1();
    println!("Hello, world!");
}
