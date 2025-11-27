mod lang;

use std::{fs::OpenOptions, io::Read};
use colored::Colorize;
use std::process::exit;
use lang::lexer;

fn main() {
    let mut file = match OpenOptions::new().read(true).create(true).write(true).open("test.fm") {
        Ok(val) => val,
        Err(err) => {
            println!("{} failed to open file: {}", "error:".red(), err);
            exit(1);
        }
    };

    let mut code = String::new();

    match file.read_to_string(&mut code) {
        Ok(_) => {},
        Err(err) => {
            println!("{} failed to read file: {}", "error:".red().bold(), err);
            exit(1);
        }
    }

    let tokens = lexer::tokenize(&code);

    println!("{:#?}", tokens);
}
