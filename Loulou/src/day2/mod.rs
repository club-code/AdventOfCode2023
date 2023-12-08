#![allow(dead_code)]

use std::cmp::max;

use crate::load_input::load_input;

fn parse_input(input: String) -> Vec<Vec<(u32,u32,u32)>> {
    input.lines()
        .map(|line| {
            line.split(": ").last().unwrap().split("; ").map(|s| {
                let mut parsed_game_result = (0, 0, 0);
                s   .split(", ")
                    .for_each( |s| {
                        print!("{s}\t");
                        let game_result = s.split(" ").collect::<Vec<&str>>();
                        for i in 0..(game_result.len()/2) {
                            let val: u32;
                            if let Ok(v) = game_result[i*2].parse::<u32>(){
                                val = v;
                            } else {
                                println!("{:?}", game_result);
                                val = 0;
                            }
                            match game_result[i*2 + 1] {
                                "red"   => parsed_game_result.0 = val,
                                "green" => parsed_game_result.1 = val,
                                "blue"  => parsed_game_result.2 = val,
                                _ => unreachable!()
                            }
                        }
                    });
                    println!("{:?}", parsed_game_result);
                    parsed_game_result
            }).collect()
        }).collect()
}

pub fn solve1() -> u32 {
    let input = load_input(2);

    parse_input(input)
        .iter()
        .enumerate()
        .filter(|(_, games)| {
            games.iter().fold(true, |flag, step| {
                    flag && step.0 < 13 && step.1 < 14 && step.2 < 15
                })
            })
        .fold(0, |acc, (id, _)| 1 + acc + id as u32 )
}

pub fn solve2() -> u32 {
    let input = load_input(2);
    parse_input(input)
        .iter()
        .map(|game| {
            let min_amounts = game.iter()
                .fold((0, 0, 0), |(racc, gacc, bacc), (r, g, b)| {
                    (max(racc,*r), max(gacc, *g), max(bacc, *b))
                });
            min_amounts.0 * min_amounts.1 * min_amounts.2
        }).sum()
}