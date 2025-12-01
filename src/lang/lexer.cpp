#include "lexer.hpp"
#include "defs.hpp"
#include <cctype>
#include <string>
#include <algorithm>
#include <util/error.hpp>

std::ostream& operator<<(std::ostream& os, const Token& token) {
	switch (token.type) {
		case TokenType::TOKEN_OPERATOR: return os << "OPERATOR(" << token.literal << ")";
		case TokenType::TOKEN_NUMBER: return os << "NUMBER(" << token.num << ")";
		case TokenType::TOKEN_SEMICOLON: return os << "SEMICOLON"; break;
		default: return os;
	}
}

std::ostream& operator<<(std::ostream& os, const Lexer& lexer) {
	os << "[" << std::endl;
	for (auto x : lexer.tokens) {
		os << "\t" << x << std::endl;
	}
	os << "]";
	return os;
}

Lexer::Lexer(std::string code): code(code), state(LexerState::LEXER_DEFAULT), lastState(LexerState::LEXER_DEFAULT), buffer(""), tokens() {}

Lexer::~Lexer() {}

void Lexer::tokenize() {
	for (auto c : code) {
		if (std::find(operators.begin(), operators.end(), c) != operators.end()) {
			state = LexerState::LEXER_OPERATOR;
			buffer += c;
		} else if (std::isdigit(c)) {
			state = LexerState::LEXER_NUMBER;
			buffer += c;
		} else if (c == ';') {
			state = LexerState::LEXER_DEFAULT;
			buffer = "";
			tokens.push_back(Token { TokenType::TOKEN_SEMICOLON, 0, "" });
		} else if (c == ' ' or c == '\n') {
			state = LexerState::LEXER_DEFAULT;
		} else {
			error("unexpected token");
		}

		if (lastState != state && lastState != LexerState::LEXER_DEFAULT && buffer != "") {
			switch (lastState) {
				case LexerState::LEXER_NUMBER: tokens.push_back(Token { TokenType::TOKEN_NUMBER, std::stoi(buffer), "" }); break;
				case LexerState::LEXER_OPERATOR: tokens.push_back(Token { TokenType::TOKEN_OPERATOR, 0, buffer }); break;
				default: break;
			}

			buffer = "";
		}

		lastState = state;
	}

	if (!buffer.empty()) {
		switch (lastState) {
			case LexerState::LEXER_NUMBER: tokens.push_back(Token { TokenType::TOKEN_NUMBER, std::stoi(buffer), "" }); break;
			case LexerState::LEXER_OPERATOR: tokens.push_back(Token { TokenType::TOKEN_OPERATOR, 0, buffer }); break;
			default: break;
		}

		buffer = "";
	}

}