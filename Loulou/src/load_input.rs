use std::fs;

use reqwest;

pub fn load_input(day: u32) -> String {
    let url = format!("https://adventofcode.com/2023/day/{day}/input");
    let cookie = fs::read_to_string("cookie.txt")
        .expect("cookie.txt not found");
    
    let client = reqwest::blocking::Client::new();
    client.get(url)
        .header("Cookie", format!("session={cookie}"))
        .send()
        .unwrap()
        .text()
        .unwrap()
}