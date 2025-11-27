use std::{process::exit};
use super::defs;
use colored::Colorize;

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
pub enum Token {
    NUMBER(i32),
    OPERATOR(String),
    SEMICOLON
}

#[derive(Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
pub enum LexerState {
    DEFAULT,
    SEMICOLON,
    NUMBER,
    OPERATOR
}

pub fn tokenize(src: &String) -> Vec<Token> {
    let mut buf: String = String::new();
    let mut tokens: Vec<Token> = vec![];
    let mut state = LexerState::DEFAULT;
    let mut last_state = state.clone();

    for i in src.chars() {
        if defs::OPERATORS.contains(&i) {
            state = LexerState::OPERATOR;
        } else if i.is_digit(10) {
            state = LexerState::NUMBER;
        } else if i == ';' {
            state = LexerState::SEMICOLON;
        } else if i == ' ' || i == '\n' {
            state = LexerState::DEFAULT;
        } else {
            println!("{} unexpected token", "error:".red().bold());
            exit(1);
        }

        if last_state != state && last_state != LexerState::DEFAULT {
            match last_state {
                LexerState::DEFAULT => {},
                LexerState::NUMBER => tokens.push(Token::NUMBER(buf.clone().parse::<i32>().unwrap_or(0))),
                LexerState::OPERATOR => tokens.push(Token::OPERATOR(buf.clone())),
                LexerState::SEMICOLON => tokens.push(Token::SEMICOLON),
                _ => {}
            }

            buf = String::new();
        }

        if state == LexerState::NUMBER || state == LexerState::OPERATOR {
            buf.push(i);
        }

        last_state = state.clone();
    }

    return tokens;
}