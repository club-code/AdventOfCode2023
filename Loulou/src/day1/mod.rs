#![allow(dead_code)]

use crate::load_input::load_input;

pub fn solve1() -> u32 {
    let input = load_input(1);

    input.lines()
        .map(|s| {
            let nums = s.chars().filter(|c| c.is_ascii_digit()).collect::<Vec<char>>();
            nums.get(0).unwrap().to_digit(10).unwrap() * 10 +
            nums.get(nums.len() - 1).unwrap().to_digit(10).unwrap()
        })
        .sum()
}

pub fn solve2() -> u32 {
    let input = load_input(1);
    
    input.lines()
        .map(|s| {
            let mut nums: Vec<u32> = Vec::new();
            for i in 0..(s.len()) {
                for j in (i)..(s.len()) {
                    let sub = s.get(i..=j).unwrap();
                    if let Ok(n) = sub.parse::<u32>() {
                        if n >9 {continue;}
                        nums.push(n);
                    }
                    if sub == "zero" {
                        nums.push(0);
                    }
                    if sub == "one" {
                        nums.push(1);
                    }
                    if sub == "two" {
                        nums.push(2);
                    }
                    if sub == "three" {
                        nums.push(3);
                    }
                    if sub == "four" {
                        nums.push(4);
                    }
                    if sub == "five" {
                        nums.push(5);
                    }
                    if sub == "six" {
                        nums.push(6);
                    }
                    if sub == "seven" {
                        nums.push(7);
                    }
                    if sub == "eight" {
                        nums.push(8);
                    }
                    if sub == "nine" {
                        nums.push(9);
                    }
                }
            }
            nums.get(0).unwrap() * 10 +
            nums.get(nums.len() - 1).unwrap()
        })
        .sum()
}